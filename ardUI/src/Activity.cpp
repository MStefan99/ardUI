//
// Created by MStefan99 on 16.12.19.
//

#include "Activity.h"


Activity::Activity(const Bundle& extras,
									 void (* onActivityResult)(int statusCode, Bundle resultData)):
	bundle {extras},
	resultCallback {onActivityResult} {
	// Nothing to do
}


Activity::~Activity() {
	delete rootView;
}


void Activity::setRootView(View* view) {
	rootView = view;
}


void Activity::setResult(int statusCode, const Bundle& data) {
	status = statusCode;
	resultData = data;
}


void Activity::finish() {
	ActivityManager::stopActivity(this);
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


const Bundle& Activity::getExtras() {
	return bundle;
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
		uint16_t widthSpec = View::MeasureSpec::makeMeasureSpec(View::MeasureSpec::EXACTLY, arduiDisplayGetWidth());
		uint16_t heightSpec = View::MeasureSpec::makeMeasureSpec(View::MeasureSpec::EXACTLY, arduiDisplayGetHeight());
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


void Activity::rewindState(Activity::State targetState) {
	while (currentState != targetState) {
		switch (currentState) {
			case Activity::State::LAUNCHED:
				create();
				break;
			case Activity::State::CREATED:
			case Activity::State::RESTARTED:
				start();
				break;
			case Activity::State::STARTED:
				resume();
				break;
			case Activity::State::RESUMED:
				pause();
				break;
			case Activity::State::PAUSED:
				if (targetState == Activity::State::RESUMED) {
					resume();
				} else {
					stop();
				}
				break;
			case Activity::State::STOPPED:
				if (targetState == Activity::State::DESTROYED) {
					destroy();
				} else {
					restart();
				}
				break;

			case Activity::State::DESTROYED:
				return;
		}
	}
}
