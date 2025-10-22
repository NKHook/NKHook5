#pragma once

namespace NKHook5 {
	namespace Classes {
		enum class eSFX_Items {
			UNKNOWN0,
			EXPLOSION,
			UNKNOWN1,
			UNKNOWN2,
			UNKNOWN3,
			UNKNOWN4,
			UNKNOWN5,
			UNKNOWN6,
			UNKNOWN7,
			UNKNOWN8,
			UNKNOWN9,
			UNKNOWN10,
			UNKNOWN11,
			UNKNOWN12,
			ANGRY_SQUIRREL,
		};

		static_assert(static_cast<int>(eSFX_Items::EXPLOSION) == 1);
		static_assert(static_cast<int>(eSFX_Items::ANGRY_SQUIRREL) == 0xE);
	}// namespace Classes

}// namespace NKHook5
