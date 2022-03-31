//
// Created by MStefan99 on 15.7.21.
//

#include "Tester.h"

#include "View.h"


int main() {
	View* v {nullptr};  // Drawable is an abstract class, using child View class

	describe("Drawable test", [&](TestSuite& suite) {
		suite.beforeEach([&] {
			v = new View;
		});

		suite.afterEach([&] {
			delete v;
		});

		suite.test("Bounds", [&] {
			Rect r {10, 20, 30, 40};

			expect(v->getBounds()).toEqual({});
			v->setBounds(r);
			expect(v->getBounds()).toEqual(r);
			v->setBounds(10, 20, 30, 40);
			expect(v->getBounds()).toEqual(r);
		});

		suite.test("Level", [&] {
			expect(v->getLevel()).toEqual(0);

			expect(v->setLevel(10)).toBeTruthy();
			expect(v->getLevel()).toEqual(10);
			expect(v->setLevel(10)).toBeFalsy();
		});

		suite.test("Padding", [&] {
			Rect r {10, 20, 30, 40};

			expect(v->getPadding()).toEqual({});
			v->setPadding(r);
			expect(v->getPadding()).toEqual(r);
			v->setPadding(10, 20, 30, 40);
			expect(v->getPadding()).toEqual(r);
		});

		suite.test("Dimensions", [&] {
			expect(v->getMinimumWidth()).toEqual(20);
			expect(v->getMinimumHeight()).toEqual(20);

			v->setMinimumWidth(40);
			v->setMinimumHeight(40);

			expect(v->getMinimumWidth()).toEqual(40);
			expect(v->getMinimumHeight()).toEqual(40);
		});

		suite.test("Visibility", [&] {
			expect(v->isVisible()).toBeTruthy();

			expect(v->setVisible(true)).toBeFalsy();
			expect(v->isVisible()).toBeTruthy();
			expect(v->setVisible(false)).toBeTruthy();
			expect(v->isVisible()).toBeFalsy();
		});
	});

	return 0;
}
