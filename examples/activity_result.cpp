//
// Created by MStefan99 on 16.12.19.
//

#include <Arduino.h>
#include "ardUI.h"


class ResultActivity: public Activity {
	using Activity::Activity;

	void onCreate() override {
		Serial.println("Hi, I am ResultActivity!");
		auto b = Bundle{};
		b.putInt("someResult", 12354);
		setResult(2, b);

		Serial.print("Exiting and returning result: ");
		Serial.println(b.getInt("someResult"));
		finish();
	}
};


class MainActivity: public Activity {
	using Activity::Activity;

	void onCreate() override {
		Serial.println("Hi, I am MainActivity!");

		Serial.println("Starting ResultActivity for result");
		startActivityForResult<ResultActivity>([](int code, Bundle results) -> void {
			Serial.print("Got result from ResultActivity: ");
			Serial.println(results.getInt("someResult"));
		});
	}
};


void setup() {
	Serial.begin(115200);
	ardUI::startFirstActivity<MainActivity>();
}


void loop() {
}