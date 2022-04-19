//
// Created by MStefan99 on 19.3.21.
//


#include "Tester.hpp"

#include "ardUI.hpp"
#include "TextView.hpp"


class TestActivity: public Activity {
	using Activity::Activity;

public:
	size_t created {};
	size_t restarted {};
	size_t started {};
	size_t resumed {};
	size_t paused {};
	size_t stopped {};
	size_t destroyed {};


	void onCreate() override {
		++created;
	}


	void onRestart() override {
		++restarted;
	}


	void onStart() override {
		++started;
	}


	void onResume() override {
		++resumed;
	}


	void onPause() override {
		++paused;
	}


	void onStop() override {
		++stopped;
	}


	void onDestroy() override {
		++destroyed;
	}
};


struct TestWrapper {
	static void run() {
		TestActivity* activity {nullptr};
		TextView* view {nullptr};

		describe("Activity tests", [&](TestSuite& suite) {

			suite.beforeEach([&] {
				activity = new TestActivity;
				view = new TextView;

				activity->setRootView(view);
			});

			suite.afterEach([&] {
				delete activity;
			});

			suite.test("Background color", [&] {
				activity->setBackgroundColor({0xfffffful});
				expect(activity->getBackgroundColor().to888()).toEqual(0xfffffful);
			});

			suite.test("Root view", [&] {
				expect(activity->getRootView()).toEqual(view);
				activity->setRootView(nullptr);
				expect(activity->getRootView()).toBeNull();
				delete view;
			});

			suite.test("Find View by ID", [&] {
				expect(activity->findViewById(view->getId())).toEqual(view);
				activity->setRootView(nullptr);
				expect(activity->findViewById(view->getId())).toBeNull();
				delete view;
			});

			suite.test("Activity lifecycle", [&] {
				activity->rewindState(Activity::CREATED);
				expect(activity->_currentState).toEqual(Activity::CREATED);
				expect(activity->created).toEqual(1);

				activity->rewindState(Activity::STARTED);
				expect(activity->_currentState).toEqual(Activity::STARTED);
				expect(activity->started).toEqual(1);

				activity->rewindState(Activity::RESUMED);
				expect(activity->_currentState).toEqual(Activity::RESUMED);
				expect(activity->resumed).toEqual(1);

				activity->rewindState(Activity::PAUSED);
				expect(activity->_currentState).toEqual(Activity::PAUSED);
				expect(activity->paused).toEqual(1);

				activity->rewindState(Activity::RESUMED);
				expect(activity->_currentState).toEqual(Activity::RESUMED);
				expect(activity->resumed).toEqual(2);

				activity->rewindState(Activity::STOPPED);
				expect(activity->_currentState).toEqual(Activity::STOPPED);
				expect(activity->paused).toEqual(2);
				expect(activity->stopped).toEqual(1);

				activity->rewindState(Activity::RESUMED);
				expect(activity->_currentState).toEqual(Activity::RESUMED);
				expect(activity->restarted).toEqual(1);
				expect(activity->started).toEqual(2);
				expect(activity->resumed).toEqual(3);

				activity->rewindState(Activity::DESTROYED);
				expect(activity->_currentState).toEqual(Activity::DESTROYED);
				expect(activity->paused).toEqual(3);
				expect(activity->stopped).toEqual(2);
				expect(activity->destroyed).toEqual(1);

				// When destroyed, an Activity can no longer change its state
				activity->rewindState(Activity::CREATED);
				expect(activity->_currentState).toEqual(Activity::DESTROYED);

				activity->rewindState(Activity::RESUMED);
				expect(activity->_currentState).toEqual(Activity::DESTROYED);
				expect(activity->destroyed).toEqual(1);
			});
		});
	}
};


void setup() {
	TestWrapper::run();
}


void loop() {
}
