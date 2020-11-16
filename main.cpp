//
// Created by MStefan99 on 16.12.19.
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

		auto ll = new LinearLayout();
		t = new TextView;
		auto b = new ButtonView();

		t->setText("Hello");
		b->setText("Press me!");
		ll->addView(t);
		ll->addView(b);
		setRootView(ll);

		ardUI::setViewName(t, "text_view");

		b->setOnClickListener([](View* view) -> void {
			Serial.println("Button pressed");
			auto t = (TextView*)ardUI::getViewByName("text_view");
			t->setText("Button pressed!");
		});
		b->setOnLongClickListener([](View* view) -> void {
			Serial.println("Button long pressed");
		});
	}


	void onResume() override {
		t->setText("Press the button!");
	}


	void onDestroy() override {
		Serial.println("MainActivity has been destroyed");
	}
};


void setup() {
	Serial.begin(115200);
	ardUI::startFirstActivity<MainActivity>();
}


void loop() {
}
