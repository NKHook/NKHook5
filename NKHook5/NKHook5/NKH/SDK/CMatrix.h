#pragma once
class CMatrix
{
public:
	union {
		float value[4][4];
		float value_arr[16];
	};
}; //Size: 0x0038