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


	void onCreate() override {
		Serial.println("Hi, I am MainActivity!");

		auto t = new TextView();
		auto ll = new LinearLayout();
		auto b = new ButtonView();

		t->setText("Hello");
		b->setText("Press me!");
		ll->addView(t);
		ll->addView(b);
		setRootView(ll);

		ardUI::setViewName(t, "hello_text");

		b->setOnClickListener([](View* b) -> void {
			auto t = (TextView*)ardUI::getViewByName("hello_text");
			t->setText("Pressed!");
		});
	}


	void onDestroy() override {
		auto t = (TextView*)ardUI::getViewByName("hello_text");
		Serial.print("Main text: ");
		Serial.println(t->getText());
		Serial.println("MainActivity has been destroyed");
	}
};


void setup() {
	Serial.begin(115200);
	ardUI::startFirstActivity<MainActivity>();
}


void loop() {
	ardUI::reset();
}
