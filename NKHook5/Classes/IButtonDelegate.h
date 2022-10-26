#pragma once

#include "CBaseButton.h"
#include "CButtonDelegateWatcher.h"
#include "SButtonCB.h"
#include "SGameTime.h"

#include <vector>

namespace NKHook5 {
	namespace Classes {
        class IButtonDelegate {
            std::vector<CBaseButton*> buttons;
            std::vector<CBaseButton*> moreButtons;
            bool avoidDuplicates = false;
            char padding[3];
            char padding_2[12];
            std::vector<CButtonDelegateWatcher*> watchers;
        public:
            virtual ~IButtonDelegate() = default;
            virtual void ButtonPressed(SButtonCB& callback) = 0;
            virtual void InputAll(SGameTime& gameTime);
            virtual void AddButton(CBaseButton* button);
            virtual void RemoveButton(CBaseButton* button);
            virtual void AddWatcher(CButtonDelegateWatcher* watcher);
            virtual void RemoveWatcher(CButtonDelegateWatcher* watcher);
        };
	}
}