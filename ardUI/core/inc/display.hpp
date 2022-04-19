//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_DISPLAY_HPP
#define ARDUI_DISPLAY_HPP

#include "Color.hpp"


namespace ardui {
	namespace display {
		enum ReturnCode {
			OK,
			FAIL,
			NOT_IMPLEMENTED,
			NOT_SUPPORTED
		};

		uint16_t getHeight();
		uint16_t getWidth();

		uint16_t getCharWidth(char c, uint16_t height);

		bool isClicked();
		uint16_t getClickX();
		uint16_t getClickY();

		ReturnCode init();

		ReturnCode on();
		ReturnCode off();
		ReturnCode setBrightness(uint8_t brightness);

		ReturnCode fill(Color color);

		ReturnCode drawPixel(int16_t x, int16_t y,
				Color color);

		ReturnCode drawLine(int16_t x1, int16_t y1,
				int16_t x2, int16_t y2,
				Color color);

		ReturnCode drawChar(int16_t x, int16_t y,
				char c, uint16_t height,
				Color color);

		ReturnCode drawText(int16_t x, int16_t y,
				const String& text, uint16_t height,
				Color color);

		ReturnCode drawCircle(int16_t x, int16_t y,
				int16_t radius,
				Color color);

		ReturnCode fillCircle(int16_t x, int16_t y,
				int16_t radius,
				Color color);

		ReturnCode drawRect(int16_t x1, int16_t y1,
				int16_t x2, int16_t y2,
				Color color);

		ReturnCode fillRect(int16_t x1, int16_t y1,
				int16_t x2, int16_t y2,
				Color color);

		ReturnCode drawTriangle(int16_t x1, int16_t y1,
				int16_t x2, int16_t y2,
				int16_t x3, int16_t y3,
				Color color);

		ReturnCode fillTriangle(int16_t x1, int16_t y1,
				int16_t x2, int16_t y2,
				int16_t x3, int16_t y3,
				Color color);

		ReturnCode drawBitmap(int16_t x, int16_t y,
				int16_t* bitmap);
	}
}

#endif //ARDUI_DISPLAY_HPP
