//
// Created by MStefan99 on 16.12.19.
//

#include <Arduino.h>
#include "ardUI.h"

#include "text_view.h"
#include "button_view.h"
#include "linear_layout.h"


class MainActivity: public Activity {
	TextView* t;


	void onCreate() override {
		Serial.println("Hi, I am MainActivity!");

		auto ll = new LinearLayout();
		t = new TextView;
		auto b = new ButtonView();

		t->setText("Hello");
		b->setText("I am a button!");
		ll->addView(t);
		ll->addView(b);
		setRootView(ll);
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
}


void loop() {
	ardUI::exit();
}
