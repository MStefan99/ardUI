//
// Created by MStefan99 on 8.7.21.
//

#include "DisplayController.h"


DisplayController::FeatureSupport DisplayController::_featureSupport {};


bool DisplayController::isSupported(ardui::display::ReturnCode code) {
	return code == ardui::display::OK;
}


void DisplayController::fill(Color color) {
	if (_featureSupport.fill) {
		ardui::display::fill(color);
	} else {
		drawRect(0, 0, ardui::display::getWidth(), ardui::display::getHeight(), color);
	}
}


void DisplayController::drawLine(uint16_t x1, uint16_t y1,
		uint16_t x2, uint16_t y2,
		Color color) {
	if (_featureSupport.drawLine) {
		ardui::display::drawLine(x1, y1, x2, y2, color);
	} else {
		auto dx = ABS(x2 - x1);
		auto dy = -ABS(y2 - y1);
		auto sx = x1 < x2? 1 : -1;
		auto sy = y1 < y2? 1 : -1;
		auto err = dx + dy;

		while (true) {
			ardui::display::drawPixel(x1, y1, color);
			if (x1 == x2 && y1 == y2) {
				break;
			}
			auto e2 = 2 * err;
			if (e2 >= dy) {
				err += dy;
				x1 += sx;
			}
			if (e2 <= dx) {
				err += dx;
				y1 += sy;
			}
		}
	}
}


void DisplayController::drawCircle(uint16_t x, uint16_t y,
		uint16_t radius,
		Color color) {
}


void DisplayController::fillCircle(uint16_t x, uint16_t y,
		uint16_t radius,
		Color color) {
}


void DisplayController::drawRect(uint16_t x1, uint16_t y1,
		uint16_t x2, uint16_t y2,
		Color color) {
	if (_featureSupport.drawRect) {
		ardui::display::drawRect(x1, y1, x2, y2, color);
	} else {
		drawLine(x1, y1, x2, y1, color);
		drawLine(x1, y1, x1, y2, color);
		drawLine(x2, y1, x2, y2, color);
		drawLine(x1, y2, x2, y2, color);
	}
}


void DisplayController::fillRect(uint16_t x1, uint16_t y1,
		uint16_t x2, uint16_t y2,
		Color color) {
	if (_featureSupport.drawRect) {
		ardui::display::fillRect(x1, y1, x2, y2, color);
	} else {
		if (y2 < y1) {
			SWAP(y1, y2)
		}
		while (y1 != y2) {
			drawLine(x1, y1, x2, y1, color);
			++y1;
		}
	}
}


void DisplayController::drawTriangle(uint16_t x1, uint16_t y1,
		uint16_t x2, uint16_t y2,
		uint16_t x3, uint16_t y3,
		Color color) {
	if (_featureSupport.drawTriangle) {
		ardui::display::drawTriangle(x1, y1, x2, y2, x3, y3, color);
	} else {
		drawLine(x1, y1, x2, y2, color);
		drawLine(x1, y1, x3, y3, color);
		drawLine(x2, y2, x3, y3, color);
	}
}


void DisplayController::fillTriangle(uint16_t x1, uint16_t y1,
		uint16_t x2, uint16_t y2,
		uint16_t x3, uint16_t y3,
		Color color) {
}


void DisplayController::drawBitmap(uint16_t x, uint16_t y,
		uint16_t* bitmap) {
}


void DisplayController::drawChar(uint16_t x, uint16_t y,
		char c, uint16_t size,
		Color color) {
	if (_featureSupport.drawChar) {
		ardui::display::drawChar(x, y, c, size, color);
	}
}


void DisplayController::drawText(uint16_t x, uint16_t y,
		const String& text, uint16_t size,
		Color color) {
	if (_featureSupport.drawText) {
		ardui::display::drawText(x, y, text, size, color);
	}
}
