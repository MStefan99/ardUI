//
// Created by MStefan99 on 8.7.21.
//

#ifndef ARDUI_DISPLAYCONTROLLER_H
#define ARDUI_DISPLAYCONTROLLER_H

#include "display.h"
#include "Color.h"
#include "font.h"


class DisplayController {
public:
	static void fill(Color color);

	static void drawLine(int16_t x1, int16_t y1,
			int16_t x2, int16_t y2,
			Color color);

	static uint16_t getCharWidth(char c, uint16_t height);

	static void drawChar(int16_t x, int16_t y,
			char c, uint16_t size,
			Color color);

	static void drawText(int16_t x, int16_t y,
			const String& text, uint16_t size,
			Color color);

	static void drawCircle(int16_t x, int16_t y,
			int16_t radius,
			Color color);

	static void fillCircle(int16_t x, int16_t y,
			int16_t radius,
			Color color);

	static void drawRect(int16_t x1, int16_t y1,
			int16_t x2, int16_t y2,
			Color color);

	static void fillRect(int16_t x1, int16_t y1,
			int16_t x2, int16_t y2,
			Color color);

	static void drawTriangle(int16_t x1, int16_t y1,
			int16_t x2, int16_t y2,
			int16_t x3, int16_t y3,
			Color color);

	static void fillTriangle(int16_t x1, int16_t y1,
			int16_t x2, int16_t y2,
			int16_t x3, int16_t y3,
			Color color);

	static void drawBitmap(int16_t x, int16_t y,
			int16_t* bitmap);

protected:
	struct FeatureSupport {
		bool fill {isSupported(ardui::display::fill({}))};
		bool drawLine {isSupported(ardui::display::drawLine(0, 0, 0, 0, {}))};
		bool drawCircle {isSupported(ardui::display::drawCircle(0, 0, 0, {}))};
		bool fillCircle {isSupported(ardui::display::fillCircle(0, 0, 0, {}))};
		bool drawRect {isSupported(ardui::display::drawRect(0, 0, 0, 0, {}))};
		bool fillRect {isSupported(ardui::display::fillRect(0, 0, 0, 0, {}))};
		bool drawTriangle {isSupported(ardui::display::drawTriangle(0, 0, 0, 0, 0, 0, {}))};
		bool fillTriangle {isSupported(ardui::display::fillTriangle(0, 0, 0, 0, 0, 0, {}))};
		bool drawBitmap {isSupported(ardui::display::drawBitmap(0, 0, nullptr))};
		bool drawChar {isSupported(ardui::display::drawChar(0, 0, ' ', 1, {}))};
		bool drawText {isSupported(ardui::display::drawText(0, 0, "", 1, {}))};
	};

	static bool isSupported(ardui::display::ReturnCode code);

	static FeatureSupport _featureSupport;
};

#endif //ARDUI_DISPLAYCONTROLLER_H
