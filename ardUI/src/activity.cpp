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


void Activity::setRootView(View* view) {
	rootView = view;
}


void Activity::create() {
	currentState = CREATED;
	onCreate();
}


void Activity::restart() {
	currentState = RESTARTED;
	onRestart();
}


void Activity::start() {
	currentState = STARTED;
	onStart();
}


void Activity::resume() {
	currentState = RESUMED;
	onResume();
}


void Activity::pause() {
	currentState = PAUSED;
	onPause();
}


void Activity::stop() {
	currentState = STOPPED;
	onStop();
}


void Activity::destroy() {
	currentState = DESTROYED;
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


View* Activity::findViewById(int id) {
	return rootView->findViewById(id);
}


View* Activity::getRootView() {
	return rootView;
}


void Activity::draw() const {
	if (rootView) {
		rootView->draw();
	}
}


void Activity::measure() {
	if (rootView) {
		int widthSpec = View::MeasureSpec::makeMeasureSpec(View::MeasureSpec::EXACTLY, arduiDisplayGetWidth());
		int heightSpec = View::MeasureSpec::makeMeasureSpec(View::MeasureSpec::EXACTLY, arduiDisplayGetHeight());
		rootView->measure(widthSpec, heightSpec);
	}
}


void Activity::layout() {
	if (rootView) {
		Rect display {0, 0, arduiDisplayGetWidth(), arduiDisplayGetHeight()};
		rootView->layout(display);
	}
}


void Activity::handleEvent(const Event& event) {
	if (rootView) {
		rootView->handleEvent(event);
	}
}
