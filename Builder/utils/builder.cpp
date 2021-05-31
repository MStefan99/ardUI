//
// Created by MStefan99 on 7.4.21.
//

#include "ardUI.h"
#include "TextView.h"
#include "ButtonView.h"
#include "LinearLayout.h"
#include "ProgressBar.h"


class SecondActivity: public Activity {
	using Activity::Activity;


	void onCreate() override {
		Serial.println("Hi, I am a second Activity!");

		auto title = new TextView("Second Activity!");
		title->setTextSize(30);
		auto t = new TextView(
				"this is a very long text that will definitely need to be broken into a few lines on the screen and even this is not enough to test whether the text will be broken correctly, so I just decided to add this part to this piece of text too just to check that my code is working properly and doesn't have any bugs which I'm sure it does because why would I do this to myself otherwise?");
		auto b = new ButtonView("Click to return");
		auto ll = new LinearLayout();
		ll->setOrientation(LinearLayout::Orientation::VERTICAL);

		auto data = getExtras();
		t->setTextColor(data.get<uint32_t>("color"));

		setRootView(ll);
		ll->addView(title);
		ll->addView(t);
		ll->addView(b);

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
		ll->setOrientation(LinearLayout::Orientation::VERTICAL);
		auto p = new ProgressBar();

		setRootView(ll);
		ll->addView(title);
		ll->addView(t);
		ll->addView(b);
		ll->addView(b2);
		ll->addView(p);

		ardUI::setViewName(t, "hello_text");
		ardUI::setViewName(p, "progress");

		b->setOnClickListener([](View* b) -> void {
			Serial.println("Button pressed!");
			auto t = (TextView*)ardUI::getViewByName("hello_text");
			t->setTextColor(t->getTextColor() & 0xffff00u?
											t->getTextColor() << 8u & 0xffffffu :
											t->getTextColor() << 8u | 0xffu & 0xffffffu);
		});

		b2->setOnClickListener([](View* b) -> void {
			Bundle data {};
			auto t = (TextView*)ardUI::getViewByName("hello_text");
			data.put<uint32_t>("color", t->getTextColor());
			ardUI::startActivity<SecondActivity>(data);
		});
	}
};


void setup() {
	ardUI::startActivity<MainActivity>();
}


void loop() {
	auto p = (ProgressBar*)ardUI::getViewByName("progress");

	auto pr = p->getProgress();
	if (pr < 100) {
		p->setProgress(p->getProgress() + 1);
	}
}
