#pragma once

#include <string>

namespace NKHook5
{
    namespace Classes
    {
        class ScriptedScreenData
        {
            std::string scriptName;
        public:
            ScriptedScreenData() = default;
            ScriptedScreenData(std::string& scriptName)
            {
                this->scriptName = scriptName;
            }
            virtual ~ScriptedScreenData() = default;
        };
    } // namespace Classes

} // namespace NKHook5
