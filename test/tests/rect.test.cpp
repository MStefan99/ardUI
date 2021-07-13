//
// Created by MStefan99 on 13.7.21.
//


#include "Tester.h"
#include "Rect.h"


int main() {
	Rect r {10, 20, 80, 100};

	test("Basic Rect functions", [&]() -> void {
		expect(r.width()).toEqual(70);
		expect(r.height()).toEqual(80);

		expect(r.centerX()).toEqual(45);
		expect(r.centerY()).toEqual(60);

		expect(r.isEmpty()).toBeFalsy();

		Rect r1 {r};
		expect(r1).toEqual(r);
		expect(r1.isEmpty()).toBeFalsy();
		r1.setEmpty();
		expect(r1.isEmpty()).toBeTruthy();
	});
}