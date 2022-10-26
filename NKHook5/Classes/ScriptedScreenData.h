#pragma once

#include "../../Signatures/Signature.h"
#include "IScreenData.h"
#include <string>

namespace NKHook5
{
    namespace Classes
    {

        class ScriptedScreenData : public IScreenData
        {
            std::string scriptName;
        public:
            ScriptedScreenData() = default;
            ScriptedScreenData(std::string scriptName)
            {
                *(void**)this = *(void**)Signatures::GetAddressOf(Sigs::ScriptedScreenData_VTable);
                this->scriptName = scriptName;
            }
            virtual ~ScriptedScreenData() = default;
        };
    } // namespace Classes

} // namespace NKHook5
