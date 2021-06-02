//
// Created by MStefan99 on 19.3.21.
//


#include "Tester.h"
#include "ardUI.h"


class ResultActivity: public Activity {
	using Activity::Activity;


	void onCreate() override {
		auto data = getExtras();

		describe("Sending data", [&](TestBlock& block) -> void {
			expect(data.getString("request")).toEqual("hello");
		});

		Bundle result {};
		result.putString("result", "success");

		setResult(0, result);
		finish();
	}
};


class TestActivity: public Activity {
	using Activity::Activity;


	void onCreate() override {
		Bundle data {};
		data.putString("request", "hello");

		startActivityForResult<ResultActivity>([](int code, Bundle results) -> void {
			describe("Returning data", [&](TestBlock& block) -> void {
				expect(code).toEqual(0);
				expect(results.getString("result")).toEqual("success");
			});
		}, data);
	}
};


void arduiUserSetup() {}


void arduiUserLoop() {}


int main() {
	ardUI::startActivity<TestActivity>();
}