//
// Created by MStefan99 on 18.7.21.
//


#include "Tester.h"

#include "TextView.h"

#include <iostream>

struct TestWrapper {
	static void run() {
		TextView* v {nullptr};

		describe("TextView test", [&](TestSuite& suite) {
			suite.beforeEach([&] {
				v = new TextView;
			});

			suite.afterEach([&] {
				delete v;
			});

			suite.test("Text", [&] {
				v->setText("test");
				expect(v->getText()).toEqual("test");

				v->append("_test");
				expect(v->getText()).toEqual("test_test");

				TextView v1 {"test1"};
				expect(v1.getText()).toEqual("test1");
			});

			suite.test("Size and color", [&] {
				v->setTextSize(50);
				expect(v->getTextSize()).toEqual(50);

				v->setTextColor({0xf0u});
				expect(v->getTextColor()).toEqual({0xf0u});
			});

			suite.test("Get lines", [&] {
				v->setText("test1");
				TextView v1 {"line1 line2"};

				expect(v->getLines(100).size()).toEqual(1);
				expect(v->getLines(100).front()).toEqual("test1");

				expect(v->getLines(1).size()).toEqual(5);
				expect(v->getLines(1).front()).toEqual("t");
				expect(v->getLines(1).back()).toEqual("1");

				expect(v->getMaxWidth()).toEqual(5 * 5);

				expect(v1.getLines(5 * 5).size()).toEqual(2);
				expect(v1.getLines(5 * 5).front()).toEqual("line1 ");
				expect(v1.getLines(5 * 5).back()).toEqual("line2");
			});
		});
	}
};


int main() {
	TestWrapper::run();

	return 0;
}

