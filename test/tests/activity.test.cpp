//
// Created by MStefan99 on 19.3.21.
//


#include "Tester.h"
#include "ardUI.h"


class ResultActivity: public Activity {
	using Activity::Activity;


	void onCreate() override {
		auto data = getExtras();

		test("Sending data", [&]() -> void {
			expect(data.getString("request")).toEqual("hello");
		});

		Bundle result {};
		result.putString("result", "success");

		setResult(1, result);
		finish();
	}
};


class TestActivity: public Activity {
	using Activity::Activity;


	void onCreate() override {
		Bundle data {};
		data.putString("request", "hello");

		startActivityForResult<ResultActivity>([](int code, Bundle results) -> void {
			test("Returning data", [&]() -> void {
				expect(code).toEqual(1);
				expect(results.getString("result")).toEqual("success");
			});
		}, data);
	}
};


void setup() {
	ardUI::startActivity<TestActivity>();

	test("Test Activity Pointer", []() -> void {
		EventManager::update(false, true);
		expect(&ardUI::getCurrentActivity()).Not().toBeNull();
		ardUI::getCurrentActivity().finish();
		EventManager::update(false, true);
		expect(&ardUI::getCurrentActivity()).toBeNull();
	});
}


void loop() {
}
