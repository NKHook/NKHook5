#pragma once

#include "S_SFXItem.h"

#include <vector>

namespace NKHook5 {
	namespace Classes {
		class C_GameSFXManager {
			char pad_0000[4];					 //0x0000
			class CGameSystemPointers* pGamePtrs = nullptr; //0x0004
			class WinSoundManager* pSoundManager = nullptr; //0x0008
			class CBloonsTD5Game* pApp = nullptr;			 //0x000C
		public:
			std::vector<S_SFXItem> mSounds;		 //0x0010
		private:
			char pad_001C[44];					 //0x001C

		public:
			static C_GameSFXManager* GetInstance();

			void Play(int id);
		};
	}// namespace Classes

}// namespace NKHook5
