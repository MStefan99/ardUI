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
		b->setText("Press me!");
		ll->addView(t);
		ll->addView(b);
		setRootView(ll);

		ardUI::setViewName(t, "text_view");

		b->setOnClickListener([](View* view) -> void {
			Serial.println("Changing text");
			auto t = (TextView*)ardUI::getViewByName("text_view");
			t->setText("Button pressed!");
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
	ardUI::showScreen<MainActivity>();
}


void loop() {
}
