//
// Created by MStefan99 on 13.7.21.
//


#include "Tester.hpp"

#include "Rect.hpp"


int main() {
	describe("Test Rect", [](TestSuite& suite) {
		suite.test("Basic Rect functions", [] {
			Rect r {10, 20, 80, 100};
			expect(r.width()).toEqual(70);
			expect(r.height()).toEqual(80);

			expect(r.centerX()).toEqual(45);
			expect(r.centerY()).toEqual(60);

			expect(r.isEmpty()).toBeFalsy();

			Rect r1 {r};
			expect(r1).toEqual(r);
			expect(r1.isEmpty()).toBeFalsy();
			expect(r1).toBeTruthy();
			r1.setEmpty();
			expect(r1.isEmpty()).toBeTruthy();
			expect(r1).toBeFalsy();
		});

		suite.test("Intersect and contain", [] {
			Rect r {10, 20, 90, 100};
			Rect r1 {20, 30, 80, 90};
			Rect r2 {100, 100, 200, 200};
			Rect r3 {200, 100, 400, 400};

			expect(r.contains(r1)).toBeTruthy();
			expect(r1.contains(r)).toBeFalsy();
			expect(r.contains(20, 30, 80, 90)).toBeTruthy();
			expect(r1.contains(10, 20, 90, 100)).toBeFalsy();

			expect(r.intersects(r1)).toBeTruthy();
			expect(r1.intersects(r)).toBeTruthy();

			expect(r2.intersects(r)).toBeFalsy();
			expect(r3.intersects(r)).toBeFalsy();
			expect(r3.intersects(r2)).toBeTruthy();

			expect(r3.intersects(0, 0, 50, 50)).toBeFalsy();
			expect(r1.intersects(50, 50, 100, 100)).toBeTruthy();
		});

		suite.test("Rect modifications", [] {
			Rect r {0, 0, 100, 100};

			r.inset(20, 10);
			expect(r.left).toEqual(20);
			expect(r.top).toEqual(10);
			expect(r.right).toEqual(80);
			expect(r.bottom).toEqual(90);

			r.inset(5, 10, 15, 20);
			expect(r.left).toEqual(25);
			expect(r.top).toEqual(20);
			expect(r.right).toEqual(65);
			expect(r.bottom).toEqual(70);

			r.inset({5, 10, 15, 20});
			expect(r.left).toEqual(30);
			expect(r.top).toEqual(30);
			expect(r.right).toEqual(50);
			expect(r.bottom).toEqual(50);

			r.set(5, 10, 15, 20);
			expect(r.left).toEqual(5);
			expect(r.top).toEqual(10);
			expect(r.right).toEqual(15);
			expect(r.bottom).toEqual(20);

			r.set({20, 15, 10, 5});
			expect(r.left).toEqual(20);
			expect(r.top).toEqual(15);
			expect(r.right).toEqual(10);
			expect(r.bottom).toEqual(5);

			r = {5, 10, 15, 20};
			expect(r.left).toEqual(5);
			expect(r.top).toEqual(10);
			expect(r.right).toEqual(15);
			expect(r.bottom).toEqual(20);

			r.offset(10, 20);
			expect(r.left).toEqual(15);
			expect(r.top).toEqual(30);
			expect(r.right).toEqual(25);
			expect(r.bottom).toEqual(40);

			r.offsetTo(10, 20);
			expect(r.left).toEqual(10);
			expect(r.top).toEqual(20);
			expect(r.right).toEqual(20);
			expect(r.bottom).toEqual(30);
		});
	});

	return 0;
}