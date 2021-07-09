//
// Created by MStefan99 on 8.7.21.
//

#include "DisplayController.h"

DisplayController::FeatureSupport DisplayController::_featureSupport {};


bool DisplayController::isSupported(ardui::display::ReturnCode code) {
	return code == ardui::display::OK;
}


void DisplayController::fill(Color color) {
}


void DisplayController::drawLine(uint16_t x1, uint16_t y1,
		uint16_t x2, uint16_t y2,
		Color color) {
	if (_featureSupport.drawLine) {
		ardui::display::DrawLine(x1, y1, x2, y2, color);
	} else {
		// TODO: implement line drawing
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
		ardui::display::DrawRect(x1, y1, x2, y2, color);
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
		ardui::display::DrawRect(x1, y1, x2, y2, color);
	} else {
		for (uint16_t i {y1}; i < y2; ++i) {
			drawLine(x1, i, x2, i, color);
		}
	}
}


void DisplayController::drawTriangle(uint16_t x1, uint16_t y1,
		uint16_t x2, uint16_t y2,
		uint16_t x3, uint16_t y3,
		Color color) {
	if (_featureSupport.drawTriangle) {
		ardui::display::DrawTriangle(x1, y1, x2, y2, x3, y3, color);
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


