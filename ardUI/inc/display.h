//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_DISPLAY_H
#define ARDUI_DISPLAY_H

#include "Color.h"


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

		uint16_t getFontHeight();
		uint16_t getCharWidth(char c, uint16_t height);

		bool isClicked();
		uint16_t getClickX();
		uint16_t getClickY();

		ReturnCode init();

		ReturnCode on();
		ReturnCode off();
		ReturnCode setBrightness(uint8_t brightness);

		ReturnCode fill(Color color);

		ReturnCode drawPixel(uint16_t x, uint16_t y,
				Color color);

		ReturnCode drawLine(uint16_t x1, uint16_t y1,
				uint16_t x2, uint16_t y2,
				Color color);

		ReturnCode drawChar(uint16_t x, uint16_t y,
				char c, uint16_t height,
				Color color);

		ReturnCode drawText(uint16_t x, uint16_t y,
				const String& text, uint16_t height,
				Color color);

		ReturnCode drawCircle(uint16_t x, uint16_t y,
				uint16_t radius,
				Color color);

		ReturnCode fillCircle(uint16_t x, uint16_t y,
				uint16_t radius,
				Color color);

		ReturnCode drawRect(uint16_t x1, uint16_t y1,
				uint16_t x2, uint16_t y2,
				Color color);

		ReturnCode fillRect(uint16_t x1, uint16_t y1,
				uint16_t x2, uint16_t y2,
				Color color);

		ReturnCode drawTriangle(uint16_t x1, uint16_t y1,
				uint16_t x2, uint16_t y2,
				uint16_t x3, uint16_t y3,
				Color color);

		ReturnCode fillTriangle(uint16_t x1, uint16_t y1,
				uint16_t x2, uint16_t y2,
				uint16_t x3, uint16_t y3,
				Color color);

		ReturnCode drawBitmap(uint16_t x, uint16_t y,
				uint16_t* bitmap);
	}
}

#endif //ARDUI_DISPLAY_H
