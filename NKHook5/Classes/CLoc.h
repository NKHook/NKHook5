#pragma once

#include "../../Util/NewFramework.h"
#include "CLoc.h"

namespace NKHook5::Classes
{
	struct SLangEntry {
		uint32_t key; //0x0000
		std::string id; //0x0004
		int32_t l; //0x001C
		std::string val; //0x0020
	};

	class SFontDef
	{
	public:
		std::string id;
		std::string name; //0x0018
		float scale; //0x0030
		uint32_t gray; //0x0034
	}; //Size: 0x0038

	class SLangText
	{
	public:
		SLangText* pProPlural; //0x0000
		SLangText* pProLoc; //0x0004
		SLangText* pPluralLoc; //0x0008
		char pad_000C[4]; //0x000C
		std::string* pLocID; //0x0010
		SLangEntry* pSLang; //0x0014
		char pad_0018[8]; //0x0018
	}; //Size: 0x0020

	struct SLanguage
	{
		std::string locale;
		std::string englishName; //0x0018
		std::string translatedName; //0x0030
		std::string xmlPath; //0x0048
		std::vector<SFontDef> fontDefs; //0x0060
		char pad_006C[4]; //0x006C
		std::vector<SLangText>* langDef; //0x0070
		char pad_0074[4]; //0x0074
		class SLangText* pLangTexts; //0x0078
		char pad_007C[84]; //0x007C
	}; //Size: 0x00D0

	class CLoc
	{
		class CBaseFileIO* pCBaseFileIO = nullptr; //0x0004
		std::vector<SLanguage*> langDefs; //0x0008
		SLanguage* pCurrentLang = nullptr; //0x0014
		SLanguage* pFallbackLang = nullptr; //0x0018
		std::string unknown_1; //0x001C
		uint32_t unknown_2 = 0;
		uint32_t unknown_3 = 0;
		std::string currentLang; //0x003C
		std::string unknown_4; //0x0054
		uint32_t unknown_5 = 0;
		uint32_t unknown_6 = 0;
		uint32_t unknown_7 = 0;
		std::string dayHourFmt; //0x0078
		std::string hourMinuteFmt; //0x0090
		std::string minuteSecondFmt; //0x00A8
		std::string secondFmt; //0x00C0
		std::string dateFmt; //0x00D8
	};
} // namespace NKHook5::Classes