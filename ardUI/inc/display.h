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

		ReturnCode Fill(uint32_t color);

		ReturnCode DrawPixel(uint16_t x, uint16_t y,
				uint32_t color);

		ReturnCode DrawLine(uint16_t x1, uint16_t y1,
				uint16_t x2, uint16_t y2,
				uint32_t color);

		ReturnCode DrawChar(uint16_t x, uint16_t y,
				char c, uint16_t height,
				uint32_t color);

		ReturnCode DrawText(uint16_t x, uint16_t y,
				const String& text, uint16_t height,
				uint32_t color);

		ReturnCode DrawCircle(uint16_t x, uint16_t y,
				uint16_t radius,
				uint32_t color);

		ReturnCode FillCircle(uint16_t x, uint16_t y,
				uint16_t radius,
				uint32_t color);

		ReturnCode DrawRect(uint16_t x1, uint16_t y1,
				uint16_t x2, uint16_t y2,
				uint32_t color);

		ReturnCode FillRect(uint16_t x1, uint16_t y1,
				uint16_t x2, uint16_t y2,
				uint32_t color);

		ReturnCode DrawTriangle(uint16_t x1, uint16_t y1,
				uint16_t x2, uint16_t y2,
				uint16_t x3, uint16_t y3,
				uint32_t color);

		ReturnCode FillTriangle(uint16_t x1, uint16_t y1,
				uint16_t x2, uint16_t y2,
				uint16_t x3, uint16_t y3,
				uint32_t color);

		ReturnCode DrawBitmap(uint16_t x, uint16_t y,
				uint16_t* bitmap);
	}
}

#endif //ARDUI_DISPLAY_H
