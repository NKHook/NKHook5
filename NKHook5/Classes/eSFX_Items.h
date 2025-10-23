#pragma once

namespace NKHook5 {
	namespace Classes {
		enum class eSFX_Items {
			NONE = -1,
			INVALID,

			/* global sfx */
			POPS = 1,
			BUY = 2,
			TAP = 3,

			/* game_sfx */
			EXPLOSION = 4,
			FROZEN_HIT = 5,
			CERAMIC_HIT = 6,
			METAL_HIT = 7,
			MOAB_HIT = 8,
			MOAB_DESTROY = 9,
			TOWER_PLACE,
			TOWER_SELL,
			TOWER_UPGRADE,
			TOWER_UNLOCK,
			TOWER_LEVEL_UP,
			GAME_OVER,
			GAME_WIN,
			ANGRY_SQUIRREL,
			BLOON_SCRAMBLER,
			BOSS_DEATH,
			SWAMP_DEATH,
			SWAMP_SPAWN,
			VORTEX_SPAWN,
			DREADBLOON_SPAWN,
			DREADBLOON_RECHARGE,
			DREADBLOON_RECHARGE_SHORT,
			DREADBLOON_ROCK_SHATTER,
			BLASTAPOPOULOS_ATTACK,
			BLASTAPOPOULOS_IMPACT,
			BLASTAPOPOULOS_INTRO,

			/* menu_sfx */
			CHEST = 4,
			SCHWING = 5,
			CHALLENGE_SPIN = 6,
			CHALLENGE_OPEN = 7,
			CHALLENGE_SHUT = 8,
			CHALLENGE_STOP = 9
		};

		static_assert(static_cast<int>(eSFX_Items::EXPLOSION) == 1);
		static_assert(static_cast<int>(eSFX_Items::ANGRY_SQUIRREL) == 0xE);
	}// namespace Classes

}// namespace NKHook5
