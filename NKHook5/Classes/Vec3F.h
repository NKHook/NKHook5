#pragma once

namespace NKHook5::Classes
{
	struct Vec3F
	{
		union
		{
			struct
			{
				float x;
				float y;
				float z;
			};
			float arr[3];
		};
	};

	static_assert(sizeof(Vec3F) == 0xC);
} // namespace NKHook5::Classes