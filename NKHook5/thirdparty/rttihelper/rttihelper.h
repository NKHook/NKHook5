#pragma once

#include "../../Utils.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

namespace h_rtti
{
	using byte = unsigned char;
	std::string bytes_to_ida_pattern(const byte* bytes, size_t size)
	{
		std::stringstream ida_pattern;
		ida_pattern << std::hex << std::setfill('0');
		for (size_t i = 0; i < size; i++)
		{
			const size_t current_byte = bytes[i];
			if (current_byte != 255)
				ida_pattern << std::setw(2) << current_byte;
			else
				ida_pattern << std::setw(1) << "?";

			if (i != size - 1)
				ida_pattern << " ";
		}

		return ida_pattern.str();
	}

	std::vector<uintptr_t> get_xrefs_to(uintptr_t address, uintptr_t start, uintptr_t size)
	{
		std::vector<uintptr_t> xrefs = {};

		// Convert the address over to an IDA pattern string
		const std::string ida_pattern = bytes_to_ida_pattern((byte*)&address, 4);

		// Get the end of the section (in our case the end of the .rdata section)
		const uintptr_t end = start + size;
		while (start && start < end)
		{
			auto xref = (uintptr_t)NKHook5::Utils::FindPattern(start, start + size, ida_pattern);

			// If the xref is 0 it means that there either were no xrefs, or there are no remaining xrefs.
			// So we should break out of our loop, otherwise it will keep on trying to look for xrefs.
			if (!xref)
				break;

			// We've found an xref, save it in the vector, and add 4 to start, so it wil now search for xrefs
			// from the previously found xref untill we're at the end of the section, or there aren't any xrefs left.
			xrefs.push_back(xref);
			start = xref + 4;
		}

		return xrefs;
	}

	bool get_section_info(uintptr_t base_address, const std::string& section_name, uintptr_t& section_start, uintptr_t& section_size)
	{
		const auto dos_header = (PIMAGE_DOS_HEADER)base_address;
		if (dos_header->e_magic != IMAGE_DOS_SIGNATURE)
			return false;

		const auto nt_headers = (PIMAGE_NT_HEADERS32)(base_address + dos_header->e_lfanew);
		if (nt_headers->Signature != IMAGE_NT_SIGNATURE)
			return false;

		PIMAGE_SECTION_HEADER section_header = IMAGE_FIRST_SECTION(nt_headers);
		uint16_t number_of_sections = nt_headers->FileHeader.NumberOfSections;
		while (number_of_sections > 0)
		{
			// If we're at the right section
			if (!strcmp(section_name.c_str(), (const char*)section_header->Name))
			{
				section_start = base_address + section_header->VirtualAddress;
				section_size = section_header->SizeOfRawData;
				return true;
			}

			section_header++;
			number_of_sections--;
		}

		return false;
	}

	size_t get_vtable(const std::string& table_name)
	{
		auto base_address = (uintptr_t)GetModuleHandleA(NULL);
		if (!base_address)
			return 0;

		// Type descriptor names look like this: .?AVC_CSPlayer@@ (so: ".?AV" + table_name + "@@")
		std::string type_descriptor_name = ".?AV" + table_name + "@@";

		// Convert the string to an IDA pattern so that we can pattern scan it
		std::string ida_pattern = bytes_to_ida_pattern((byte*)type_descriptor_name.data(), type_descriptor_name.size());

		auto rtti_type_descriptor = (uintptr_t)NKHook5::Utils::FindPattern(ida_pattern);
		if (!rtti_type_descriptor) {
			// If we fail, try again with AU
			type_descriptor_name = ".?AU" + table_name + "@@";

			// Convert the string to an IDA pattern so that we can pattern scan it
			ida_pattern = bytes_to_ida_pattern((byte*)type_descriptor_name.data(), type_descriptor_name.size());

			rtti_type_descriptor = (uintptr_t)NKHook5::Utils::FindPattern(ida_pattern);
			if (!rtti_type_descriptor) {
				return 0;
			}
		}

		// We're doing - 0x8 here, because the location of the rtti_type_descriptor is 0x8 bytes before the string (open up client_panorama.dll in IDA and take a look) 
		rtti_type_descriptor -= 0x8;

		// We only need to get xrefs that are inside the .rdata section (there sometimes are xrefs in .text, so we have to filter them out)
		uintptr_t rdata_start = 0, rdata_size = 0;
		if (!get_section_info(base_address, ".rdata", rdata_start, rdata_size))
			return 0;

		// Get all xrefs to the type_descriptor
		const std::vector<uintptr_t> xrefs = get_xrefs_to(rtti_type_descriptor, rdata_start, rdata_size);
		for (const uintptr_t xref : xrefs)
		{
			// xref - 0x8 = offset of this vtable in complete class (from top)
			// So if it's 0 it means it's the class we need, and not some class it inherits from (again, opening up client_panorama.dll in IDA will help you understand)
			const int32_t offset_from_class = *(int32_t*)(xref - 0x8);
			if (offset_from_class != 0)
				continue;

			// We've found the correct xref, the object locator is 0xC bytes before the xref. (Again, client_panorama.dll yada yada yada)
			const uintptr_t object_locator = xref - 0xC;

			// Now we need to get an xref to the object locator, as that's where the vtable is located
			{
				// Convert the object locator address to an IDA pattern
				ida_pattern = bytes_to_ida_pattern((byte*)&object_locator, 4);

				const size_t vtable_address = NKHook5::Utils::FindPattern(rdata_start, rdata_start + rdata_size, ida_pattern.c_str()) + 0x4;

				// Here I'm checking for <= 4 as we're adding 0x4 to it. So if the pattern scan returns 0 we still head the fuck out
				if (vtable_address <= 4)
					return 0;

				// We've now found the vtable address, however, we probably want a pointer to the vtable (which is in .text).
				// To do this, we're going to find a reference to the vtable address, and use that as pointer.

				// If you don't need a pointer to the vtable in your implementation however, just return vtable_address
				return vtable_address;
				// I don't need this, so I will just return it
				/*
				uintptr_t text_start = 0, text_size = 0;
				if (!get_section_info(base_address, ".text", text_start, text_size))
					return nullptr;

				// Convert the vtable address to an IDA pattern
				ida_pattern = bytes_to_ida_pattern((byte*)&vtable_address, 4);
				return (uintptr_t*)NKHook5::Utils::FindPattern(text_start, text_start + text_size, ida_pattern.c_str());
				*/
			}
		}

		// We for some odd reason didn't find any valid xrefs
		return 0;
	}
}