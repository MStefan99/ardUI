//
// Created by MStefan99 on 9.7.21.
//

#ifndef ARDUI_COLOR_H
#define ARDUI_COLOR_H

#include "platform.h"


class Color final {
public:
	Color() = default;
	Color(const Color& color) = default;

	Color(uint32_t color);
	// TODO: fix ambiguity
//	Color(uint16_t color);

	uint32_t to888() const;
	uint16_t to565() const;

	Color& operator=(uint32_t color);
	Color& operator=(uint16_t color);

	bool operator==(const Color& c) const;
	bool operator!=(const Color& c) const;

	Color& operator=(const Color& c) = default;

protected:
	#if COLOR_MODE == COLOR_888

	class ColorData {
	public:
		ColorData() = default;

		explicit ColorData(uint32_t color);
		explicit ColorData(uint16_t color);

		ColorData& operator=(uint32_t color);
		ColorData& operator=(uint16_t color);

		bool operator==(const ColorData& c) const;
		bool operator!=(const ColorData& c) const;

		explicit operator uint16_t() const;
		explicit operator uint32_t() const;

	protected:
		uint8_t _r {};
		uint8_t _g {};
		uint8_t _b {};
	};

	ColorData _color {};
	#else
	uint16_t _color {};
	#endif
};

#endif //ARDUI_COLOR_H