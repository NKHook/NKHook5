#pragma once
class CBloonEscapedEvent
{
public:
	char pad_0000[4]; //0x0000
	class CBloon* EscapedBloon; //0x0004

public:
	class CBloon& getEscapedBloon() {
		return *this->EscapedBloon;
	}
}; //Size: 0x0008