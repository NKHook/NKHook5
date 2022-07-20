#ifndef NKHOOK5_CLASSES_CLOC
#define NKHOOK5_CLASSES_CLOC

#include <ghstl/string>
#include <ghstl/vector>

namespace NKHook5
{
    namespace Classes
    {
        enum class Texts {
            LOC_NULL = 0x0,
            LOC_DECIMAL = 0x1,
            LOC_DELIMITER = 0x2,
            LOC_MM_Chest_ComeBack = 0x27,
            LOC_MM_BUILDING_Temple = 0x31,
            LOC_MM_BUILDING_Settings = 0xA9,
            LOC_SETTINGS_Controls = 0xAB,
            LOC_SETTINGS_DragDrop = 0xAC,
            LOC_SETTINGS_DropLock = 0xAD,
            LOC_SETTINGS_Language = 0xAE,
            LOC_SETTINGS_Copyright = 0xAF,
            LOC_MISC_LimitedTime = 0x19B
        };

        struct SLang {
            uint32_t key; //0x0000
            ghstl::string id; //0x0004
            int32_t l; //0x001C
            ghstl::string val; //0x0020
        };

        class SFontDef
        {
        public:
            ghstl::string id;
            ghstl::string name; //0x0018
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
            ghstl::string* pLocID; //0x0010
            SLang* pSLang; //0x0014
            char pad_0018[8]; //0x0018
        }; //Size: 0x0020

        class SLangDef
        {
        public:
            ghstl::string locale;
            ghstl::string englishName; //0x0018
            ghstl::string translatedName; //0x0030
            ghstl::string xmlPath; //0x0048
            ghstl::vector<SFontDef> fontDefs; //0x0060
            char pad_006C[4]; //0x006C
            ghstl::vector<SLangText>* langDef; //0x0070
            char pad_0074[4]; //0x0074
            class SLangText* pLangTexts; //0x0078
            char pad_007C[84]; //0x007C
        }; //Size: 0x00D0

        class CLoc
        {
            class CBaseFileIO* pCBaseFileIO = nullptr; //0x0004
            std::vector<SLangDef*> langDefs; //0x0008
            SLangDef* pCurrentLang = nullptr; //0x0014
            SLangDef* pFallbackLang = nullptr; //0x0018
            ghstl::string unknown_1; //0x001C
            uint32_t unknown_2 = 0;
            uint32_t unknown_3 = 0;
            ghstl::string currentLang; //0x003C
            ghstl::string unknown_4; //0x0054
            uint32_t unknown_5 = 0;
            uint32_t unknown_6 = 0;
            uint32_t unknown_7 = 0;
            ghstl::string dayHourFmt; //0x0078
            ghstl::string hourMinuteFmt; //0x0090
            ghstl::string minuteSecondFmt; //0x00A8
            ghstl::string secondFmt; //0x00C0
            ghstl::string dateFmt; //0x00D8
        };
    } // namespace Classes

} // namespace NKHook5
#endif /* NKHOOK5_CLASSES_CLOC */