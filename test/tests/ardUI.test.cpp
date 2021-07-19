//
// Created by MStefan99 on 19.3.21.
//

#include "Tester.h"

#include "ardUI.h"


class TestActivity: public Activity {
	using Activity::Activity;


	void onCreate() override {
	}
};


struct TestWrapper {
	static void run() {
		describe("ardUI test", [&](TestSuite& suite) {
			suite.test("Switching Activities", [] {
				ardUI::startActivity<TestActivity>();
				EventManager::update(true);

				auto firstActivity {ActivityManager::_currentActivity};
				auto& currentActivity {ActivityManager::_currentActivity};

				expect(firstActivity).Not().toBeNull();
				expect(firstActivity->_currentState).toEqual(Activity::RESUMED);

				ardUI::startActivity<TestActivity>();
				EventManager::update(true);
				expect(firstActivity->_currentState).toEqual(Activity::STOPPED);
				expect(currentActivity->_currentState).toEqual(Activity::RESUMED);

				ardUI::getCurrentActivity()->finish();
				EventManager::update(true);
				expect(firstActivity->_currentState).toEqual(Activity::RESUMED);

				ardUI::getCurrentActivity()->finish();
				EventManager::update(true);
				expect(currentActivity).toBeNull();
			});

			suite.test("Activity stack", [] {
				for (unsigned int i {0}; i < BACK_STACK_DEPTH + 10; ++i) {
					ardUI::startActivity<TestActivity>();
					EventManager::update(true);
					expect(ActivityManager::_backList.size()).toBeLessThanOrEqual(BACK_STACK_DEPTH);
				}

				ardUI::back();
				EventManager::update(true);
				expect(ActivityManager::_backList.size()).toEqual(BACK_STACK_DEPTH - 1);

				ardUI::reset();
				EventManager::update(true);
				expect(ActivityManager::_backList.empty()).toBeTruthy();
			});
		});
	}
};


void setup() {
	TestWrapper::run();
}


void loop() {
}
