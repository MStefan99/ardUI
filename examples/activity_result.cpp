//
// Created by MStefan99 on 16.12.19.
//

#include <Arduino.h>

#include "ardUI.hpp"


class ResultActivity: public Activity {
	using Activity::Activity;


	void onCreate() override {
		Serial.println("Hi, I am ResultActivity!");
		auto b = Bundle {};
		b.putInt("someResult", 12354);
		setResult(2, b);

		Serial.print("Exiting and returning result: ");
		Serial.println(b.getInt("someResult"));
		finish();
	}


	void onDestroy() override {
		Serial.println("ResultActivity is destroyed");
	}
};


class MainActivity: public Activity {
	using Activity::Activity;


	void onCreate() override {
		Serial.println("MainActivity is created");

		Serial.println("Starting ResultActivity for result");
		startActivityForResult<ResultActivity>([](int code, Bundle results) -> void {
			Serial.print("Got result from ResultActivity: ");
			Serial.println(results.getInt("someResult"));
			ardUI::getCurrentActivity()->finish();
		});
		Serial.println("Doing other things...");
	}


	void onResume() override {
		Serial.println("MainActivity is resumed");
	}


	void onPause() override {
		Serial.println("MainActivity is paused");
	}


	void onDestroy() override {
		Serial.println("MainActivity is destroyed");
	}
};


void setup() {
	Serial.begin(115200);
	ardUI::startActivity<MainActivity>();
}


void loop() {
	Serial.println("Loop");
}
