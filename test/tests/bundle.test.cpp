//
// Created by MStefan99 on 16.11.20.
//


#include "Tester.h"
#include "Bundle.h"


void arduiUserSetup() {}


void arduiUserLoop() {}


struct A {
	int val;


	bool operator==(const A& other) const {
		return val == other.val;
	}
};


int main() {
	Bundle b {};
	describe("Bundle Test", [&](TestSuite& block) -> void {

		block.test("Testing int", [&]() -> void {
			b.putInt("int", 1);
			expect(b.getInt("int")).toEqual(1);
		});

		block.test("Testing float", [&]() -> void {
			b.putFloat("float", 1.1);
			expect(b.getFloat("float")).toEqual(1.1);
		});

		block.test("Testing string", [&]() -> void {
			b.putString("string", "Test");
			expect(b.getString("string")).toEqual("Test");
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
			expect(b.getString("string")).toEqual("Test");
			expect(b.get<A>("custom")).toEqual(A {1});
		});

		block.test("Bundle copying", [&]() -> void {
			Bundle b1 {b};
			expect(b1.getInt("int")).toEqual(1);
			expect(b1.getFloat("float")).toEqual(1.1);
			expect(b1.getString("string")).toEqual("Test");
			expect(b1.get<A>("custom")).toEqual(A {1});
		});
	});
}

