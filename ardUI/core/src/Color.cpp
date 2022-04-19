//
// Created by MStefan99 on 9.7.21.
//

#include "Color.hpp"


#if COLOR_MODE == COLOR_888


Color::ColorData::ColorData(uint32_t color):
		_r {static_cast<uint8_t>((color & 0xFF0000ul) >> 16u)},
		_g {static_cast<uint8_t>((color & 0xFF00u) >> 8u)},
		_b {static_cast<uint8_t>(color & 0xFFu)} {
	// Nothing to do
}


Color::ColorData& Color::ColorData::operator=(uint32_t color) {
	_r = static_cast<uint8_t>((color & 0xFF0000ul) >> 16u);
	_g = static_cast<uint8_t>((color & 0xFF00u) >> 8u);
	_b = static_cast<uint8_t>(color & 0xFFu);
	return *this;
}


Color::ColorData::operator uint32_t() const {
	return (static_cast<uint32_t>(_r) << 16u)
			| (static_cast<uint32_t>(_g) << 8u)
			| static_cast<uint32_t>(_b);
}


Color::ColorData::operator uint16_t() const {
	return static_cast<uint16_t>((_r & 0xF8u) << 8u)
			| static_cast<uint16_t>((_g & 0xFCu) << 3u)
			| static_cast<uint16_t>((_b & 0xF8u) >> 3u);
}


bool Color::ColorData::operator==(const ColorData& c) const {
	return _r == c._r && _g == c._g && _b == c._b;
}


bool Color::ColorData::operator!=(const ColorData& c) const {
	return _r != c._r || _g != c._g || _b != c._b;
}


Color::Color(uint32_t color): _color {color} {
	// Nothing to do
}


Color& Color::operator=(uint32_t color) {
	_color = color;
	return *this;
}


uint32_t Color::to888() const {
	return static_cast<uint32_t>(_color);
}


#else


static uint32_t ShiftColor(uint32_t number, uint8_t shift, uint8_t lsb = 0, uint8_t fillBits = 3) {
	number <<= shift;

	if (number >> (lsb + fillBits) & 1u) {
		number |= ((1u << fillBits) - 1u) << lsb;
	}
	return number;
}


static uint16_t To565(uint32_t color) {
	return static_cast<uint16_t>(
			((color & 0xF80000ul) >> 8u) |
					((color & 0xFC00u) >> 5u) |
					((color & 0xF8u) >> 3u));
}


static uint32_t To888(uint16_t color) {
	return static_cast<uint32_t>(
			ShiftColor((color & 0xF800ul), 8, 16) |
					ShiftColor((color & 0x7E0u), 5, 8, 2) |
					ShiftColor((color & 0x1Fu), 3));
}


Color::Color(uint32_t color):
		_color {To565(color)} {
	// Nothing to do
}


Color& Color::operator=(uint32_t color) {
	_color = To565(color);
	return *this;
}


uint32_t Color::to888() const {
	return To888(_color);
}


#endif


uint16_t Color::to565() const {
	return static_cast<uint16_t>(_color);
}


bool Color::operator==(const Color& c) const {
	return _color == c._color;
}


bool Color::operator!=(const Color& c) const {
	return _color != c._color;
}
