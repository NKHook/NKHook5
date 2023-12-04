#pragma once

namespace NKHook5::Classes
{
	struct Vec2F
	{
		union
		{
			struct
			{
				float x;
				float y;
			};
			float arr[2]{};
		};
	public:
		Vec2F() {
			this->x = 0;
			this->y = 0;
		}
		Vec2F(float x, float y) {
			this->x = x;
			this->y = y;
		}
	};

	static_assert(sizeof(Vec2F) == 0x8);
} // namespace NKHook5::Classes