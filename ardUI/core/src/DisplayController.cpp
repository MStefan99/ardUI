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
		drawRect(0, 0,
				static_cast<int16_t>(ardui::display::getWidth()),
				static_cast<int16_t>(ardui::display::getHeight()), color);
	}
}


void DisplayController::drawLine(int16_t x1, int16_t y1,
		int16_t x2, int16_t y2,
		Color color) {
	if (_featureSupport.drawLine) {
		ardui::display::drawLine(x1, y1, x2, y2, color);
	} else {
		auto dx = ABS(x2 - x1);
		auto dy = -ABS(y2 - y1);
		auto sx = x1 < x2? 1: -1;
		auto sy = y1 < y2? 1: -1;
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


void DisplayController::drawCircle(int16_t x, int16_t y,
		int16_t radius,
		Color color) {
}


void DisplayController::fillCircle(int16_t x, int16_t y,
		int16_t radius,
		Color color) {
}


void DisplayController::drawRect(int16_t x1, int16_t y1,
		int16_t x2, int16_t y2,
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


void DisplayController::fillRect(int16_t x1, int16_t y1,
		int16_t x2, int16_t y2,
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


void DisplayController::drawTriangle(int16_t x1, int16_t y1,
		int16_t x2, int16_t y2,
		int16_t x3, int16_t y3,
		Color color) {
	if (_featureSupport.drawTriangle) {
		ardui::display::drawTriangle(x1, y1, x2, y2, x3, y3, color);
	} else {
		drawLine(x1, y1, x2, y2, color);
		drawLine(x1, y1, x3, y3, color);
		drawLine(x2, y2, x3, y3, color);
	}
}


void DisplayController::fillTriangle(int16_t x1, int16_t y1,
		int16_t x2, int16_t y2,
		int16_t x3, int16_t y3,
		Color color) {
}


void DisplayController::drawBitmap(int16_t x, int16_t y,
		int16_t* bitmap) {
}


uint16_t DisplayController::getCharWidth(char c, uint16_t height) {
	if (_featureSupport.drawChar) {
		return ardui::display::getCharWidth(c, height);
	} else {
		return height;
	}
}


void DisplayController::drawChar(int16_t x, int16_t y,
		char c, uint16_t size,
		Color color) {
	if (_featureSupport.drawChar) {
		ardui::display::drawChar(x, y, c, size, color);
	} else {
		auto pxSize = uint8_t(size / 8);

		for (uint8_t j {0}; j < 8; ++j) {
			for (uint8_t i {0}; i < 8; ++i) {
				if (ardui::LETTERS[static_cast<unsigned char>(c)][j] >> i & 1u) {  // TODO: optimize, fix signedness
					ardui::display::fillRect(x + pxSize * i, y + pxSize * j, x + pxSize * i + pxSize, y + pxSize * j + pxSize,
							color);
				}
			}
		}
	}
}


void DisplayController::drawText(int16_t x, int16_t y,
		const String& text, uint16_t size,
		Color color) {
	if (_featureSupport.drawText) {
		ardui::display::drawText(x, y, text, size, color);
	} else {
		auto str = text.c_str();
		uint16_t i {0};

		while (*str) {
			drawChar(static_cast<int16_t>(x + (size * i++)), y, *str, size, color);
			++str;
		}
	}
}
