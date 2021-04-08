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
		auto ll = new LinearLayout();
		auto b = new ButtonView();

		t->setText("Hello");
		b->setText("Press me!");
		ll->addView(t);
		ll->addView(b);
		activity->setRootView(ll);

		ardUI::setViewName(t, "hello_text");

		b->setOnClickListener([](View* b) -> void {
			auto t = (TextView*)ardUI::getViewByName("hello_text");
			t->setText("Pressed!");
		});
	}
};


class BuilderActivity: public Activity {
	using Activity::Activity;

	void onCreate() override {
		setContentView<Layout>();
	}
};


void setup() {
	ardUI::startFirstActivity<BuilderActivity>();
}

void loop() {

}
