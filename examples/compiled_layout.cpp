//
// Created by MStefan99 on 7.4.21.
//

#include "ardUI.h"
#include "TextView.h"
#include "ButtonView.h"
#include "LinearLayout.h"


struct Layout {
	static void fill(Activity* activity) {
		Serial.println("Hi, I am MainActivity!");

		auto t = new TextView();
		activity->setRootView(t);

		ardUI::setViewName(t, "hello_text");
	}
};


class MainActivity: public Activity {
	using Activity::Activity;


	void onCreate() override {
		setContentView<Layout>();
	}
};


void setup() {
	ardUI::startActivity<MainActivity>();
}


void loop() {
}
