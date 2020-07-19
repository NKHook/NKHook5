#pragma once
class CMatrix
{
public:
	union {
		float value[4][4];
		float value_arr[16];
	};

public:
	CMatrix() {
		for (int i = 0; i < 16; i++)
			value_arr[i] = 0;
	}
	CMatrix(int nullInitialize) {
		for(int i = 0; i<16; i++)
			value_arr[i] = 0;
		if (nullInitialize != 0) {
			value_arr[4] = 1.0f;
			value_arr[9] = 1.0f;
			value_arr[14] = 1.0f;
		}
	}
}; //Size: 0x0038