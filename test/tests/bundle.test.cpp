//
// Created by MStefan99 on 16.11.20.
//


#include "Tester.h"
#include "Bundle.h"


void arduiUserSetup() {}


void arduiUserLoop() {}


struct A {
	int val;


	bool operator ==(const A& other) const {
		return val == other.val;
	}
};


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

		block.test("Testing string", [&]() -> void {
			b.putString("string", "test");
			expect(b.getString("string")).toEqual("test");
		});

		block.test("Testing custom type", [&]() -> void {
			b.put<int>("otherInt", 2);
			expect(b.get<int>("otherInt")).toEqual(2);
			b.put<A>("custom", A {1});
			expect(b.get<A>("custom")).toEqual(A {1});
		});

		block.test("Out-of-scope retrieval", [&]() -> void {
			expect(b.getInt("int")).toEqual(1);
			expect(b.getFloat("float")).toEqual(1.1);
			expect(b.getString("string")).toEqual("test");
			expect(b.get<A>("custom")).toEqual(A {1});
		});
	});
}

