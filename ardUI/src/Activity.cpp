//
// Created by MStefan99 on 16.12.19.
//

#include "Activity.h"


Activity::Activity(const Bundle& extras,
		void (* onActivityResult)(int statusCode, Bundle resultData)):
		_bundle {extras},
		_resultCallback {onActivityResult} {
	// Nothing to do
}


Activity::~Activity() {
	delete _rootView;
}


void Activity::setRootView(View* view) {
	_rootView = view;
}


void Activity::setResult(int statusCode, const Bundle& data) {
	_status = statusCode;
	_resultData = data;
}


void Activity::finish() {
	ActivityManager::stopActivity(this);
}


void Activity::create() {
	_currentState = CREATED;
	onCreate();
}


void Activity::restart() {
	_currentState = RESTARTED;
	onRestart();
}


void Activity::start() {
	_currentState = STARTED;
	onStart();
}


void Activity::resume() {
	_currentState = RESUMED;
	onResume();
}


void Activity::pause() {
	_currentState = PAUSED;
	onPause();
}


void Activity::stop() {
	_currentState = STOPPED;
	onStop();
}


void Activity::destroy() {
	_currentState = DESTROYED;
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
	return _rootView->findViewById(id);
}


const Bundle& Activity::getExtras() {
	return _bundle;
}


View* Activity::getRootView() {
	return _rootView;
}


void Activity::measure() {
	if (_rootView) {
		uint16_t widthSpec = View::MeasureSpec::makeMeasureSpec(View::MeasureSpec::EXACTLY, arduiDisplayGetWidth());
		uint16_t heightSpec = View::MeasureSpec::makeMeasureSpec(View::MeasureSpec::EXACTLY, arduiDisplayGetHeight());
		_rootView->measure(widthSpec, heightSpec);
	}
}


void Activity::layout() {
	if (_rootView) {
		Rect display {0, 0, arduiDisplayGetWidth(), arduiDisplayGetHeight()};
		_rootView->layout(display);
	}
}


void Activity::draw() const {
	if (_rootView) {
		if (!_rootView->_valid) {
			arduiDisplayFill(_backgroundColor);
		}
		_rootView->draw();
	}
}


void Activity::handleEvent(const Event& event) {
	if (_rootView) {
		_rootView->handleEvent(event);
	}
}


void Activity::rewindState(Activity::State targetState) {
	while (_currentState != targetState) {
		switch (_currentState) {
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
