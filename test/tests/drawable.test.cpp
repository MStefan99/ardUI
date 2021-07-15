//
// Created by MStefan99 on 15.7.21.
//

#include "Tester.h"

#include "View.h"



int main() {
	View* v {nullptr};  // Drawable is an abstract class, using child View class

	describe("Drawable test", [&](TestSuite& suite) -> void {
		suite.beforeEach([&]() -> void {
			v = new View;
		});

		suite.afterEach([&]() -> void {
			delete v;
		});

		suite.test("Bounds", [&]() -> void {
			Rect r {10, 20, 30, 40};

			expect(v->getBounds()).toEqual({});
			v->setBounds(r);
			expect(v->getBounds()).toEqual(r);
			v->setBounds(10, 20, 30, 40);
			expect(v->getBounds()).toEqual(r);
		});

		suite.test("Level", [&]() -> void {
			expect(v->getLevel()).toEqual(0);

			expect(v->setLevel(10)).toBeTruthy();
			expect(v->getLevel()).toEqual(10);
			expect(v->setLevel(10)).toBeFalsy();
		});

		suite.test("Padding", [&]() -> void {
			Rect r {10, 20, 30, 40};

			expect(v->getPadding()).toEqual({});
			v->setPadding(r);
			expect(v->getPadding()).toEqual(r);
			v->setPadding(10, 20, 30, 40);
			expect(v->getPadding()).toEqual(r);
		});
		
		suite.test("Dimensions", [&]() -> void {
			expect(v->getMinimumWidth()).toEqual(20);
			expect(v->getMinimumHeight()).toEqual(20);
			
			v->setMinimumWidth(40);
			v->setMinimumHeight(40);

			expect(v->getMinimumWidth()).toEqual(40);
			expect(v->getMinimumHeight()).toEqual(40);
		});

		suite.test("Visibility", [&]() -> void {
			expect(v->isVisible()).toBeTruthy();

			expect(v->setVisible(true)).toEqual(false);
			expect(v->isVisible()).toBeTruthy();
			expect(v->setVisible(false)).toEqual(true);
			expect(v->isVisible()).toBeFalsy();
		});
	});
}
