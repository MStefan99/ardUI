//
// Created by MStefan99 on 16.11.20.
//


#include "Tester.h"
#include "Bundle.h"


void arduiUserSetup() {}


void arduiUserLoop() {}


int main() {
	describe("Bundle test", [](TestBlock& block) -> void {
		Bundle b {};

		block.test("Testing int", [&]() -> void {
			b.putInt("int", 1);
			expect(b.getInt("int")).toEqual(1);
		});

		block.test("Testing float", [&]() -> void {
			b.putFloat("float", 1.1);
			expect(b.getFloat("float")).toEqual(1.1);
		});

		block.test("Out-of-scope retrieval", [&]() -> void {
			expect(b.getInt("int")).toEqual(1);
			expect(b.getFloat("float")).toEqual(1.1);
		});
	});
}

