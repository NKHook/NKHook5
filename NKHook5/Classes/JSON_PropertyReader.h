#pragma once

#include "../Util/NewFramework.h"
#include "CFlagStringConvertor.h"
#include "Json.h"

#include <string>

namespace NKHook5::Classes
{
	template<typename type_t>
	std::optional<type_t> ReadPrimitive(const nfw::map<nfw::string, JsonValue>& jsonData, const nfw::string& key) noexcept
	{
		if(jsonData.empty() || !jsonData.contains(key))
			return {};

		auto& value = jsonData.at(key);
		if(value.is_null())
			return {};
		return value.get_value<type_t>();
	}

	class JSON_PropertyReader
	{
	public:
		nfw::map<nfw::string, JsonValue>* mData{};
		nfw::map<nfw::string, JsonValue>* mOtherData{};
		char padding_0008[8]{};
		bool reading = false;
		float N000023D7 = 1.0f;
		float N000023D8 = 1.0f;

		template<typename adjust_t>
		void Adjust(nfw::map<nfw::string, JsonValue>& a, nfw::map<nfw::string, JsonValue>& b)
		{

		}

		template<typename type_t>
		std::optional<type_t> ReadPrimitive(const nfw::string& key) const
		{
			if(this->mData->empty())
				return {};

			auto& value = this->mData->at(key);
			if(value.is_null())
				return {};
			return value.get_value<type_t>();
		}

		/*void Read(uint32_t& flags, CFlagStringConvertor* convertor, int category, nfw::string& key)
		{
			ReadFromObject(flags, key)
		}

		template<typename type_t>
		void ReadFromObject(type_t& data, const nfw::string& key)
		{
			if(this->reading)
			{
				const auto& iter = this->mData->find(key);
				if(iter != this->mData->end())
				{
					//Throw JSON_PropertyException
				}
				auto success = GetValueFromObject(this->mData, key, data);
				if(!success)
					return;
			}
		}

		template<typename type_t>
		static bool GetValueFromObject(nfw::map<nfw::string, json_spirit::Value> const* objectData, type_t& value, const nfw::string& key)
		{
			if(objectData == nullptr)
				return false;

			const auto& iter = objectData->find(key);
			if(iter != objectData->end()) {
				value = *iter;
				return true;
			}

			return false;
		}*/
	};
}