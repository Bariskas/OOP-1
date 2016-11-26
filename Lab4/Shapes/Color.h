#pragma once
class CColor final
{
public:
	CColor() = default;
	CColor(uint8_t r, uint8_t g, uint8_t b);
	std::string ToString() const;
	bool operator ==(CColor other) const;
	friend std::istream& operator >>(std::istream& stream, CColor& color);

	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;
};

