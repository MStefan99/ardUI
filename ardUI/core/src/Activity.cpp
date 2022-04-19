//
// Created by MStefan99 on 16.12.19.
//

#include "Activity.hpp"


Activity::Activity(const Bundle& extras,
		void (* onActivityResult)(int statusCode, Bundle resultData)):
		_bundle {extras},
		_resultCallback {onActivityResult} {
	// Nothing to do
}


Activity::~Activity() {
	delete _rootView;
	delete _dialog;
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


void Activity::showDialog(Dialog* dialog) {
	if (_dialog) {
		_dialog->onStop();
	}

	_dialog = dialog;
	_dialog->_ownerActivity = this;
	_dialog->onCreate();
}


void Activity::dismissDialog() {
	if (_dialog) {
		_dialog->onStop();
		_dialog->_ownerActivity = nullptr;
		_dialog = nullptr;
	}
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
	if (_rootView) {
		return _rootView->findViewById(id);
	} else {
		return nullptr;
	}
}


const Bundle& Activity::getExtras() {
	return _bundle;
}


View* Activity::getRootView() {
	return _rootView;
}


void Activity::measure(View::MeasureSpec widthMeasureSpec, View::MeasureSpec heightMeasureSpec) {
	if (_dialog) {
		_dialog->measure(widthMeasureSpec, heightMeasureSpec);
	} else if (_rootView) {
		_rootView->measure(widthMeasureSpec, heightMeasureSpec);
	}
}


void Activity::layout(int16_t left, int16_t top, int16_t right, int16_t bottom) {
	if (_dialog) {
		_dialog->layout(left, top, right, bottom);
	} else if (_rootView) {
		_rootView->layout(left, top, right, bottom);
	}
}


void Activity::draw() const {
	if (_dialog) {
		_dialog->draw();
	} else if (_rootView) {
		if (!_rootView->_valid) {
			DISPLAY_UTIL::fill(_backgroundColor);
		}
		_rootView->draw();
	}
}


View* Activity::handleEvent(const Event& event) {
	if (_dialog) {
		auto v {_dialog->handleEvent(event)};
		if (!v) {
			dismissDialog();
		}
		return v;
	} else if (_rootView) {
		return _rootView->handleEvent(event);
	}
	return nullptr;
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


Color Activity::getBackgroundColor() const {
	return _backgroundColor;
}


void Activity::setBackgroundColor(Color backgroundColor) {
	_backgroundColor = backgroundColor;
}
