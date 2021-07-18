//
// Created by MStefan99 on 18.7.21.
//

#include "Tester.h"

#include "ButtonView.h"


int main() {
	describe("ButtonView test", [&](TestSuite& suite) {
		suite.test("Text", [] {
			ButtonView v {"btn"};

			expect(v.getText()).toEqual("btn");
		});

		suite.test("Border color", [] {
			ButtonView v {};

			v.setBorderColor({0xffu});
			expect(v.getBorderColor()).toEqual({0xffu});
		});
	});

	return 0;
}
