//
// Created by MStefan99 on 16.12.19.
//

#include <Arduino.h>
#include "ardUI.h"

#include "text_view.h"


class MainActivity: public Activity {
	TextView* t;


	void onCreate() override {
		Serial.println("Hi, I am MainActivity!");

		t = new TextView;
		t->setText("Hello");
		this->setRootView(t);
	}


	void onResume() override {
		t->setText("Hello, I am textview!");
	}


	void onDestroy() override {
		Serial.println("MainActivity has been destroyed");
	}
};


void setup() {
	ardUI::showScreen<MainActivity>();
	ardUI::exit();
}


void loop() {
}
