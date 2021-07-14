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
		auto view = new TextView {};

		describe("Activity tests", [&](TestSuite& suite) -> void {

			suite.beforeEach([]() -> void {
				ardUI::startActivity<TestActivity>();
				EventManager::update(false, true);
			});

			suite.afterEach([]() -> void {
				if (ardUI::getCurrentActivity()) {
					ardUI::getCurrentActivity()->finish();
					EventManager::update(false, true);
				}
			});

			suite.test("Activity lifecycle", []() -> void {
				auto firstActivity {ActivityManager::_currentActivity};
				auto& currentActivity {ActivityManager::_currentActivity};

				expect(firstActivity).Not().toBeNull();
				expect(firstActivity->_currentState).toEqual(Activity::RESUMED);

				ardUI::startActivity<TestActivity>();
				EventManager::update(false, true);
				expect(firstActivity->_currentState).toEqual(Activity::STOPPED);
				expect(currentActivity->_currentState).toEqual(Activity::RESUMED);

				ardUI::getCurrentActivity()->finish();
				EventManager::update(false, true);
				expect(firstActivity->_currentState).toEqual(Activity::RESUMED);

				ardUI::getCurrentActivity()->finish();
				EventManager::update(false, true);
				expect(currentActivity).toBeNull();
			});

			suite.test("Background color", []() -> void {
				ardUI::getCurrentActivity()->setBackgroundColor({0xfffffful});
				expect(ardUI::getCurrentActivity()->getBackgroundColor().to888()).toEqual(0xfffffful);
			});

			suite.test("Root view", [&]() -> void {
				ardUI::getCurrentActivity()->setRootView(view);
				expect(ardUI::getCurrentActivity()->getRootView()).toEqual(view);
			});
		});
	}
};


void setup() {
	TestWrapper::run();
}


void loop() {
}
