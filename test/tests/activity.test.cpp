//
// Created by MStefan99 on 19.3.21.
//


#include "Tester.h"
#include "ardUI.h"


class ResultActivity: public Activity {
	using Activity::Activity;


	void onCreate() override {
		auto data = getExtras();
		expect(data.getInt("request")).toEqual(1);

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
		data.putInt("request", 1);

		startActivityForResult<ResultActivity>([](int code, Bundle results) -> void {
			expect(code).toEqual(0);
			expect(results.getString("result")).toEqual("success");
		}, data);
	}
};


void arduiUserSetup() {}


void arduiUserLoop() {}


int main() {
	ardUI::startFirstActivity<TestActivity>();
}