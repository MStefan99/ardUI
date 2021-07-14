//
// Created by MStefan99 on 19.3.21.
//


#include "Tester.h"

#include "ardUI.h"
#include "TextView.h"


class TestActivity: public Activity {
	using Activity::Activity;


	void onCreate() override {
	}
};


struct TestWrapper {
	static void run() {
		Activity* activity {nullptr};
		TextView* view {nullptr};

		describe("Activity tests", [&](TestSuite& suite) -> void {

			suite.beforeEach([&]() -> void {
				activity = new TestActivity;
				view = new TextView;

				activity->setRootView(view);
			});

			suite.afterEach([&]() -> void {
				delete activity;
			});

			suite.test("Background color", [&]() -> void {
				activity->setBackgroundColor({0xfffffful});
				expect(activity->getBackgroundColor().to888()).toEqual(0xfffffful);
			});

			suite.test("Root view", [&]() -> void {
				expect(activity->getRootView()).toEqual(view);
				activity->setRootView(nullptr);
				expect(activity->getRootView()).toBeNull();
				delete view;
			});

			suite.test("Find View by ID", [&]() -> void {
				expect(activity->findViewById(view->getId())).toEqual(view);
				activity->setRootView(nullptr);
				expect(activity->findViewById(view->getId())).toBeNull();
				delete view;
			});

			suite.test("Activity lifecycle", [&]() -> void {
				activity->rewindState(Activity::CREATED);
				expect(activity->_currentState).toEqual(Activity::CREATED);

				activity->rewindState(Activity::STARTED);
				expect(activity->_currentState).toEqual(Activity::STARTED);

				activity->rewindState(Activity::RESUMED);
				expect(activity->_currentState).toEqual(Activity::RESUMED);

				activity->rewindState(Activity::PAUSED);
				expect(activity->_currentState).toEqual(Activity::PAUSED);

				activity->rewindState(Activity::RESTARTED);
				expect(activity->_currentState).toEqual(Activity::RESTARTED);

				activity->rewindState(Activity::STOPPED);
				expect(activity->_currentState).toEqual(Activity::STOPPED);

				activity->rewindState(Activity::DESTROYED);
				expect(activity->_currentState).toEqual(Activity::DESTROYED);

				activity->rewindState(Activity::CREATED);
				expect(activity->_currentState).toEqual(Activity::DESTROYED);

				activity->rewindState(Activity::RESUMED);
				expect(activity->_currentState).toEqual(Activity::DESTROYED);
			});
		});
	}
};


void setup() {
	TestWrapper::run();
}


void loop() {
}
