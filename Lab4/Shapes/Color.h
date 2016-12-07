#pragma once
class CColor final
{
public:
	CColor() = default;
	CColor(uint8_t r, uint8_t g, uint8_t b);
	std::string ToString() const;
	bool operator ==(CColor other) const;

	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;
};

std::istream& operator >> (std::istream& stream, CColor& color);