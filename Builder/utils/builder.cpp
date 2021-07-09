//
// Created by MStefan99 on 7.4.21.
//

#include "ardUI.h"
#include "TextView.h"
#include "ButtonView.h"
#include "LinearLayout.h"
#include "ConstraintLayout.h"
#include "ProgressBar.h"
#include "ListView.h"
#include "ArrayAdapter.h"
#include "BuilderInterface.h"


class SecondActivity;

class ConstraintActivity;


class StringAdapter: public ArrayAdapter<String> {
	using ArrayAdapter<String>::ArrayAdapter;

public:
	View* getView(int position) const override {
		return new TextView(getItem(position));
	}
};


class MainActivity: public Activity {
	using Activity::Activity;
	String* _stringArray = new String[] {"a", "b", "c", "d", "e"};
	StringAdapter* _stringAdapter = new StringAdapter(_stringArray, 4);


	void onCreate() override {
		Serial.println("Hi, I am a first Activity!");

		auto title = new TextView("First Activity");
		title->setTextSize(30);
		auto t = new TextView("Hello!");
		auto b = new ButtonView("Update text");
		auto b2 = new ButtonView("Open another Activity");
		auto b3 = new ButtonView("See the miracles of constraints!");
		auto ll = new LinearLayout();
		ll->setOrientation(LinearLayout::Orientation::VERTICAL);
		auto p = new ProgressBar();
		auto lv = new ListView<String>();
		lv->setAdapter(_stringAdapter);

		setRootView(ll);
		ll->addView(title);
		ll->addView(t);
		ll->addView(b);
		ll->addView(b2);
		ll->addView(b3);
		ll->addView(lv);
		ll->addView(p);

		ardUI::setViewName(t, "hello_text");
		ardUI::setViewName(p, "progress");

		b->setOnClickListener([](View* b) -> void {
			Serial.println("Button pressed!");
			auto t = (TextView*)ardUI::getViewByName("hello_text");
			auto color {t->getTextColor().to888()};
			t->setTextColor(color & 0xffff00u?
			                color << 8u & 0xffffffu :
			                color << 8u | 0xffu & 0xffffffu);
		});

		b2->setOnClickListener([](View* b) -> void {
			Bundle data {};
			auto t = (TextView*)ardUI::getViewByName("hello_text");
			data.put<Color>("color", t->getTextColor());
			ardUI::startActivity<SecondActivity>(data);
		});

		b3->setOnClickListener([](View* b) -> void {
			ardUI::startActivity<ConstraintActivity>();
		});
	}


	void onDestroy() override {
		// Destroying everything we've allocated
		delete _stringAdapter;
		delete[] _stringArray;
	}
};


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
		t->setTextColor(data.get<Color>("color"));

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


class ConstraintActivity: public Activity {
	using Activity::Activity;


	void onCreate() override {
		auto cl = new ConstraintLayout();

		auto bv = new ButtonView("back");
		auto tv = new TextView("text");
		auto tv2 = new TextView("other text");
		auto bv2 = new ButtonView("also back");
		bv->setPadding(2, 4, 8, 16);
		auto backCallback = [](View* v) -> void {
			ardUI::back();
		};
		bv->setOnClickListener(backCallback);
		bv2->setOnClickListener(backCallback);
		cl->addView(bv);
		cl->addView(tv);
		cl->addView(tv2);
		cl->addView(bv2);
		setRootView(cl);

		auto constraints = cl->getConstraints();
		constraints->connect(bv, ConstraintLayout::LEFT, cl, ConstraintLayout::LEFT, 16);
		constraints->connect(bv, ConstraintLayout::TOP, cl, ConstraintLayout::TOP, 32);
		constraints->connect(bv, ConstraintLayout::RIGHT, cl, ConstraintLayout::RIGHT, 200);
		constraints->connect(tv, ConstraintLayout::LEFT, bv, ConstraintLayout::RIGHT, 8);
		constraints->connect(tv, ConstraintLayout::TOP, bv, ConstraintLayout::BOTTOM, 4);
		constraints->connect(tv2, ConstraintLayout::RIGHT, cl, ConstraintLayout::RIGHT, 32);
		constraints->connect(tv2, ConstraintLayout::BOTTOM, cl, ConstraintLayout::BOTTOM, 16);
		constraints->connect(bv2, ConstraintLayout::TOP, tv, ConstraintLayout::BOTTOM, 4);
		constraints->connect(bv2, ConstraintLayout::RIGHT, tv2, ConstraintLayout::LEFT, 8);
		constraints->connect(bv2, ConstraintLayout::BOTTOM, cl, ConstraintLayout::BOTTOM, 16);
		constraints->connect(bv2, ConstraintLayout::LEFT, cl, ConstraintLayout::LEFT, 64);
	}
};


void setup() {
	ardUI::startActivity<MainActivity>();
}


void loop() {
	auto p = (ProgressBar*)ardUI::getViewByName("progress");

	if (p) {
		auto pr = p->getProgress();
		if (pr < 100) {
			p->setProgress(p->getProgress() + 1);
			delay(25);
		}
	}
}
