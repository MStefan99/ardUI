//
// Created by MStefan99 on 15.7.21.
//

#include <vector>
#include <iostream>

#include "Tester.h"
#include "Color.h"


int main() {
	std::vector<std::pair<uint32_t, uint16_t>> testColors {
			{0x0, 0x0},
			{0xfffffful, 0xffffu},
			{0xff0000ul, 0xf800u},
			{0xff00ul, 0x7e0u},
			{0xfful, 0x1fu}
	};

	describe("Color test", [&](TestSuite& suite) -> void {
		suite.test("Color conversions", [&]() -> void {
			Color color;

			for (auto c: testColors) {
				color = c.first;

				expect(Color {c.first}.to888()).toEqual(c.first);
				expect(color.to888()).toEqual(c.first);

				expect(Color {c.first}.to565()).toEqual(c.second);
				expect(color.to565()).toEqual(c.second);
			}
		});

		suite.test("Color copy", [&]() -> void {
			for (auto c: testColors) {
				Color c1 {c.first};
				Color c2 {c1};
				Color c3 {0x1u};

				expect(c1.to888()).toEqual(c.first);
				expect(c2.to888()).toEqual(c.first);
				expect(c3.to888()).Not().toEqual(c.first);
			}
		});

		suite.test("Color comparison", [&]() -> void {
			for (auto c: testColors) {
				Color c1 {c.first};
				Color c2 {c.first};
				Color c3 {0x1u};

				expect(c1).toEqual(c2);
				expect(c3).Not().toEqual(c1);
				expect(c3).Not().toEqual(c2);
			}
		});
	});
}
