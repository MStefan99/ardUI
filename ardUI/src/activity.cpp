//
// Created by MStefan99 on 16.12.19.
//

#include "activity.h"


Activity::~Activity() {
	delete rootView;
}


template <class compiledLayout>
void Activity::setContentView(compiledLayout layoutClass) {
	layoutClass.fill();  // "fill()" function must be present in the compiled layout
}


void Activity::setContentView(const String& xml) {
	LayoutInflater::inflate(xml, *rootView);
}


void Activity::setRootView(View* view) {
	rootView = view;
}


void Activity::create() {
	currentState = Created;
	onCreate();
}


void Activity::restart() {
	currentState = Restarted;
	onRestart();
}


void Activity::start() {
	currentState = Started;
	onStart();
}


void Activity::resume() {
	currentState = Resumed;
	onResume();
}


void Activity::pause() {
	currentState = Paused;
	onPause();
}


void Activity::stop() {
	currentState = Stopped;
	onStop();
}


void Activity::destroy() {
	currentState = Destroyed;
	onDestroy();
}


void Activity::onCreate() {
	// Nothing to do
}


void Activity::onStart() {
	// Nothing to do
}


void Activity::onRestart() {
	// Nothing to do
}


void Activity::onResume() {
	// Nothing to do
}


void Activity::onPause() {
	// Nothing to do
}


void Activity::onStop() {
	// Nothing to do
}


void Activity::onDestroy() {
	// Nothing to do
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
