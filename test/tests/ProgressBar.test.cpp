//
// Created by MStefan99 on 18.7.21.
//

#include "Tester.hpp"

#include "ProgressBar.hpp"


int main() {
	ProgressBar* bar {nullptr};

	describe("ProgressBar test", [&](TestSuite& suite) {
		suite.beforeEach([&] {
			bar = new ProgressBar;
		});

		suite.afterEach([&] {
			delete bar;
		});

		suite.test("Progress", [&] {
			bar->setProgress(0);
			expect(bar->getProgress()).toEqual(0);

			bar->setProgress(100);
			expect(bar->getProgress()).toEqual(100);

			bar->setMin(-100);
			bar->setMax(0);

			expect(bar->getMin()).toEqual(-100);
			expect(bar->getMax()).toEqual(0);

			bar->setProgress(-100);
			expect(bar->getProgress()).toEqual(-100);

			bar->setProgress(0);
			expect(bar->getProgress()).toEqual(0);
		});

		suite.test("Colors", [&] {
			bar->setBackgroundColor({0xffu});
			expect(bar->getBackgroundColor()).toEqual({0xffu});

			bar->setBarColor({0x7fu});
			expect(bar->getBarColor()).toEqual({0x7fu});
		});
	});

	return 0;
}
