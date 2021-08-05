//
// Created by MStefan99 on 5.8.21.
//

#include "Tester.h"

#include "Activity.h"
#include "TextView.h"

static size_t CREATED {};
static size_t STOPPED {};


class TestDialog: public Dialog {
public:
	void onCreate() override {
		++CREATED;
	}

	void onStop() override {
		++STOPPED;
	}
};


class TestActivity: public Activity {
	using Activity::Activity;

public:
	void onCreate() override {
		auto d {new TestDialog};

		d->setRootView(new TextView("dialog view"));
		showDialog(d);
	}
};


struct TestWrapper {
	static void run() {
		describe("Test Dialog", [&](TestSuite& suite) {
			suite.test("Lifecycle", [&] {
				expect(CREATED).toEqual(0);

				TestActivity a {};
				a.rewindState(Activity::RESUMED);

				expect(CREATED).toEqual(1);
				expect(STOPPED).toEqual(0);

				a.dismissDialog();

				expect(STOPPED).toEqual(1);
			});

			suite.test("Owner Activity", [&] {
				TestActivity a {};
				a.rewindState(Activity::RESUMED);

				expect(&a).toEqual(dynamic_cast<TestActivity*>(a._dialog->getOwnerActivity()));
			});
		});
	}
};


int main() {
	TestWrapper::run();

	return 0;
}
