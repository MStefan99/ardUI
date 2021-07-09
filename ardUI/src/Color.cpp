//
// Created by MStefan99 on 9.7.21.
//

#include "Color.h"


#if COLOR_MODE == COLOR_888


Color::ColorData::ColorData(uint32_t color):
		_r {(uint8_t)((color & 0xFF0000ul) >> 16u)},
		_g {(uint8_t)((color & 0xFF00u) >> 8u)},
		_b {(uint8_t)((color & 0xFFu))} {
	// Nothing to do
}


Color::ColorData& Color::ColorData::operator=(uint32_t color) {
	_r = (uint8_t)(color & 0xFF0000ul) >> 16u;
	_g = (uint8_t)(color & 0xFF00u) >> 8u;
	_b = (uint8_t)(color & 0xFFu);
	return *this;
}


Color::ColorData& Color::ColorData::operator=(uint16_t color) {
	_r = (uint8_t)(color & 0xF80000ul) >> 8u;
	_g = (uint8_t)(color & 0xFC00u) >> 5u;
	_b = (uint8_t)(color & 0xF8u) >> 3u;
	return *this;
}


Color::ColorData::operator uint32_t() const {
	return ((uint32_t)_r << 16u) | ((uint32_t)_g << 8u) | (uint32_t)_b;
}


Color::ColorData::operator uint16_t() const {
	return (uint16_t)(_r << 8u) | (uint16_t)(_g << 5u) | (uint16_t)_b;  // NOLINT(hicpp-signed-bitwise)
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
	return (uint32_t)_color;
}


#else


static uint32_t Expand(uint32_t number, uint8_t amount, uint8_t lsb) {
	if (number >> lsb & 1u) {
		for (uint8_t i {0}; i < amount; ++i) {
			number = number << 1u | 0x1u << lsb;
		}
		return number;
	} else {
		return number << amount;
	}
}


Color::Color(uint32_t color): _color {(uint16_t)color} {
	// Nothing to do
}


Color& Color::operator=(uint32_t color) {
	_color = (uint16_t)color;
	return *this;
}


uint32_t Color::to888() const {
	return Expand((_color & 0xF800ul), 8, 11) |
			Expand((_color & 0x7E0u), 5, 5) |
			Expand((_color & 0x1Fu), 3, 0);
}


#endif


uint16_t Color::to565() const {
	return (uint16_t)_color;
}


bool Color::operator==(const Color& c) const {
	return _color == c._color;
}


bool Color::operator!=(const Color& c) const {
	return _color != c._color;
}
