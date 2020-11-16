//
// Created by MStefan99 on 16.12.19.
//

#include <Arduino.h>
#include "ardUI.h"

#include "TextView.h"
#include "ButtonView.h"
#include "LinearLayout.h"


class ResultActivity: public Activity {
	using Activity::Activity;

	void onCreate() override {
		Serial.println("Hi, I am ResultActivity!");
		auto b = Bundle{};
		b.putInt("someResult", 12354);
		setResult(2, b);
		ardUI::back();
	}
};


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

		startActivityForResult<ResultActivity>(1);
	}


	void onResume() override {
		t->setText("Press the button!");
	}


	void onActivityResult(int requestCode, int resultCode, const Bundle &results) override {
		Serial.print("Received Activity result. Request code: ");
		Serial.print(requestCode);
		Serial.print(" , Result code: ");
		Serial.println(resultCode);
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
