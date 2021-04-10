//
// Created by MStefan99 on 7.4.21.
//

#include "ardUI.h"
#include "TextView.h"
#include "ButtonView.h"
#include "LinearLayout.h"


class SecondActivity: public Activity {
	using Activity::Activity;


	void onCreate() override {
		Serial.println("Hi, I am a second Activity!");

		auto title = new TextView("Second Activity!");
		title->setTextSize(30);
		auto b = new ButtonView("Click to return");
		auto ll = new LinearLayout();

		ll->addView(title);
		ll->addView(b);
		setRootView(ll);

		b->setOnClickListener([](View* b) -> void {
			Serial.println("Back pressed");
			ardUI::back();
		});
	}
};


class MainActivity: public Activity {
	using Activity::Activity;


	void onCreate() override {
		Serial.println("Hi, I am a first Activity!");

		auto title = new TextView("First Activity");
		title->setTextSize(30);
		auto t = new TextView("Hello!");
		auto b = new ButtonView("Update text");
		auto b2 = new ButtonView("Open another Activity");
		auto ll = new LinearLayout();

		ll->addView(title);
		ll->addView(t);
		ll->addView(b);
		ll->addView(b2);
		setRootView(ll);

		ardUI::setViewName(t, "hello_text");

		b->setOnClickListener([](View* b) -> void {
			Serial.println("Button pressed!");
			auto t = (TextView*)ardUI::getViewByName("hello_text");
			t->setTextColor(t->getTextColor() & 0xffff00u?
											t->getTextColor() << 8u & 0xffffffu :
											t->getTextColor() << 8u | 0xffu & 0xffffffu);
		});

		b2->setOnClickListener([](View* b) -> void {
			ardUI::startActivity<SecondActivity>();
		});
	}
};


void setup() {
	ardUI::startActivity<MainActivity>();
}


void loop() {
}
