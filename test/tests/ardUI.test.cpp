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
		describe("ardUI and EventManager", [&](TestSuite& suite) -> void {
			suite.test("Switching Activities", []() -> void {
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
		});
	}
};


void setup() {
	TestWrapper::run();
}


void loop() {
}
