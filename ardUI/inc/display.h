//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_DISPLAY_H
#define ARDUI_DISPLAY_H

#include "platform.h"


namespace ardui {
	namespace display {
		enum ReturnCode {
			OK,
			FAIL,
			NOT_IMPLEMENTED,
			NOT_SUPPORTED
		};

		uint16_t GetHeight();
		uint16_t GetWidth();

		uint16_t GetFontHeight();
		uint16_t GetCharWidth(char c, uint16_t height);

		bool IsClicked();
		uint16_t GetClickX();
		uint16_t GetClickY();

		ReturnCode Init();

		ReturnCode On();
		ReturnCode Off();
		ReturnCode SetBrightness(uint8_t brightness);

		ReturnCode Fill(Color color);

		ReturnCode DrawPixel(uint16_t x, uint16_t y,
				Color color);

		ReturnCode DrawLine(uint16_t x1, uint16_t y1,
				uint16_t x2, uint16_t y2,
				Color color);

		ReturnCode DrawChar(uint16_t x, uint16_t y,
				char c, uint16_t height,
				Color color);

		ReturnCode DrawText(uint16_t x, uint16_t y,
				const String& text, uint16_t height,
				Color color);

		ReturnCode DrawCircle(uint16_t x, uint16_t y,
				uint16_t radius,
				Color color);

		ReturnCode FillCircle(uint16_t x, uint16_t y,
				uint16_t radius,
				Color color);

		ReturnCode DrawRect(uint16_t x1, uint16_t y1,
				uint16_t x2, uint16_t y2,
				Color color);

		ReturnCode FillRect(uint16_t x1, uint16_t y1,
				uint16_t x2, uint16_t y2,
				Color color);

		ReturnCode DrawTriangle(uint16_t x1, uint16_t y1,
				uint16_t x2, uint16_t y2,
				uint16_t x3, uint16_t y3,
				Color color);

		ReturnCode FillTriangle(uint16_t x1, uint16_t y1,
				uint16_t x2, uint16_t y2,
				uint16_t x3, uint16_t y3,
				Color color);

		ReturnCode DrawBitmap(uint16_t x, uint16_t y,
				uint16_t* bitmap);
	}
}

#endif //ARDUI_DISPLAY_H
