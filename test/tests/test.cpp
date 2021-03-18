//
// Created by MStefan99 on 18.3.21.
//

#include "Tester.h"


void arduiUserSetup() {}


void arduiUserLoop() {}


int main() {
	describe("Bundle test", [](TestBlock& block) -> void {

		block.test("Testing with int", [&]() -> void {
		});

		block.test("Testing with float", [&]() -> void {
		});

		block.afterAll([&]() -> void {

		});

		block.beforeAll([&]() -> void {

		});
	});
}
