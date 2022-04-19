//
// Created by MStefan99 on 13.7.21.
//

#include "Tester.hpp"


void describe(const std::string& desc, const std::function<void(TestSuite&)>& cb) {
	TestSuite block {desc, cb};
}


void test(const std::string& desc, const std::function<void()>& cb) {
	describe(desc, [&](TestSuite& block) -> void {
		block.test(desc, [&]() -> void {
			cb();
		});
	});
}
