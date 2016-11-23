#pragma once
class CColor final
{
public:
	CColor(std::string colorStr);
	CColor(uint8_t r, uint8_t g, uint8_t b);
	std::string ToString();

	uint8_t r;
	uint8_t g;
	uint8_t b;

private:
	uint8_t StrToUint8(std::string str);
};

