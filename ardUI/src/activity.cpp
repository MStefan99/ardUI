//
// Created by MStefan99 on 16.12.19.
//

#include "activity.h"


Activity::~Activity() {
	delete rootView;
}


template<class compiledLayout>
void Activity::setContentView(compiledLayout layoutClass) {
	layoutClass.fill();  // "fill()" function must be present in the compiled layout
}


void Activity::setContentView(const String& xml) {
	LayoutInflater::inflate(xml, *rootView);
}


void Activity::setRootView(View *view){
	rootView = view;
}


void Activity::onCreate() {
	currentState = Created;
}


void Activity::onStart() {
	currentState = Started;
}


void Activity::onRestart() {
	currentState = Restarted;
}


void Activity::onResume() {
	currentState = Resumed;
}


void Activity::onPause() {
	currentState = Paused;
}


void Activity::onStop() {
	currentState = Stopped;
}


void Activity::onDestroy() {
	currentState = Destroyed;
}


void Activity::draw() const {
	if (rootView) {
		rootView->draw();
	}
}


View* Activity::findViewById(int id) {
	return rootView->findViewById(id);
}


View* Activity::getRootView() {
	return rootView;
}


void Activity::measure() {
	int widthSpec = View::MeasureSpec::makeMeasureSpec(View::MeasureSpec::EXACTLY, arduiDisplayGetWidth());
	int heightSpec = View::MeasureSpec::makeMeasureSpec(View::MeasureSpec::EXACTLY, arduiDisplayGetHeight());
	rootView->measure(widthSpec, heightSpec);
}


void Activity::layout() {
	Rect display {0, 0, arduiDisplayGetWidth(), arduiDisplayGetHeight()};
	rootView->layout(display);
}
