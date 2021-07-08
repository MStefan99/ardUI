//
// Created by MStefan99 on 8.7.21.
//

#ifndef ARDUI_DISPLAYCONTROLLER_H
#define ARDUI_DISPLAYCONTROLLER_H

#include "display.h"


class DisplayController {
public:
	static void fill(uint32_t color);

	static void drawLine(uint16_t x1, uint16_t y1,
			uint16_t x2, uint16_t y2,
			uint32_t color);

	static void drawCircle(uint16_t x, uint16_t y,
			uint16_t radius,
			uint32_t color);

	static void fillCircle(uint16_t x, uint16_t y,
			uint16_t radius,
			uint32_t color);

	static void drawRect(uint16_t x1, uint16_t y1,
			uint16_t x2, uint16_t y2,
			uint32_t color);

	static void fillRect(uint16_t x1, uint16_t y1,
			uint16_t x2, uint16_t y2,
			uint32_t color);

	static void drawTriangle(uint16_t x1, uint16_t y1,
			uint16_t x2, uint16_t y2,
			uint16_t x3, uint16_t y3,
			uint32_t color);

	static void fillTriangle(uint16_t x1, uint16_t y1,
			uint16_t x2, uint16_t y2,
			uint16_t x3, uint16_t y3,
			uint32_t color);

	static void drawBitmap(uint16_t x, uint16_t y,
			uint16_t* bitmap);

protected:
	struct FeatureSupport {
		bool fill {isSupported(ardui::display::Fill(0))};
		bool drawLine {isSupported(ardui::display::DrawLine(0, 0, 0, 0, 0))};
		bool drawCircle {isSupported(ardui::display::DrawCircle(0, 0, 0, 0))};
		bool fillCircle {isSupported(ardui::display::FillCircle(0, 0, 0, 0))};
		bool drawRect {isSupported(ardui::display::DrawRect(0, 0, 0, 0, 0))};
		bool fillRect {isSupported(ardui::display::FillRect(0, 0, 0, 0, 0))};
		bool drawTriangle {isSupported(ardui::display::DrawTriangle(0, 0, 0, 0, 0, 0, 0))};
		bool fillTriangle {isSupported(ardui::display::FillTriangle(0, 0, 0, 0, 0, 0, 0))};
		bool drawBitmap {isSupported(ardui::display::DrawBitmap(0, 0, nullptr))};
	};

	static bool isSupported(ardui::display::ReturnCode code);

	static FeatureSupport _featureSupport;
};

#endif //ARDUI_DISPLAYCONTROLLER_H
