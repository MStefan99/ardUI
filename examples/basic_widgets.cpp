//
// Created by MStefan99 on 22.3.21.
//

#include <Arduino.h>
#include "ardUI.h"

#include "TextView.h"
#include "ButtonView.h"
#include "LinearLayout.h"


class MainActivity: public Activity {
	using Activity::Activity;
	TextView* t;


	void onCreate() override {
		Serial.println("Hi, I am MainActivity!");

		t = new TextView();
		auto ll = new LinearLayout();
		auto b = new ButtonView();

		t->setText("Hello");
		b->setText("Press me!");
		ll->addView(t);
		ll->addView(b);
		setRootView(ll);

		ardUI::setViewName(b, "button_view");
	}


	void onResume() override {
		t->setText("Press the button!");
	}


	void onDestroy() override {
		auto b = (ButtonView*)ardUI::getViewByName("button_view");
		Serial.print("Button text: ");
		Serial.println(b->getText());
		Serial.println("MainActivity has been destroyed");
	}
};


void setup() {
	Serial.begin(115200);
	ardUI::startFirstActivity<MainActivity>();
	ardUI::reset();
}


void loop() {
}
