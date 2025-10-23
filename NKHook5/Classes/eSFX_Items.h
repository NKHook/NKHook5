#pragma once

namespace NKHook5 {
	namespace Classes {
		enum class eSFX_Items : int16_t {
			NONE = -1,

			/* global sfx */
			POPS = 0,
			BUY = 1,
			TAP = 2,

			/* game_sfx */
			EXPLOSION = 3,
			FROZEN_HIT = 4,
			CERAMIC_HIT = 5,
			METAL_HIT = 6,
			MOAB_HIT = 7,
			MOAB_DESTROY = 8,
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
			CHEST = 3,
			SCHWING = 4,
			CHALLENGE_SPIN = 5,
			CHALLENGE_OPEN = 6,
			CHALLENGE_SHUT = 7,
			CHALLENGE_STOP = 8
		};
	}// namespace Classes

}// namespace NKHook5
