//
// Created by MStefan99 on 16.12.19.
//

#include <Arduino.h>
#include "ardUI.h"

#include "text_view.h"


class MainActivity: public Activity {
	TextView *t;

	void onCreate() override {
		Serial.println("Hi, I am MainActivity!");

		t = new TextView;
		this->setRootView(t);
	}

	void onDestroy() override {
		delete t;
		Serial.println("MainActivity has been destroyed");
	}
};


void setup() {
	ardUI::showScreen<MainActivity>();
}


void loop() {
}
