//
// Created by MStefan99 on 19.3.21.
//


#include "Tester.hpp"

#include "ardUI.hpp"


class ResultActivity: public Activity {
	using Activity::Activity;


	void onCreate() override {
		auto data = getExtras();

		test("Sending data", [&] {
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

		startActivityForResult<ResultActivity>([](int code, Bundle results) {
			test("Returning data", [&] {
				expect(code).toEqual(1);
				expect(results.getString("result")).toEqual("success");
			});
		}, data);
	}
};


void setup() {
	ardUI::startActivity<TestActivity>();
}


void loop() {
}
