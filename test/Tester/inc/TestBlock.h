//
// Created by MStefan99 on 16.11.20.
//

#ifndef ARDUI_TESTBLOCK_H
#define ARDUI_TESTBLOCK_H


#include <functional>
#include <list>

#include "AssertException.h"
#include "Test.h"


class TestBlock {
public:
	TestBlock() = default;

	explicit TestBlock(const std::string& name):
			name {name} {}

	~TestBlock() {
		run();
	}

	bool run() {
		try {
			blockCallback();
			if (beforeCallback) {
				beforeCallback();
			}
			for (const auto& test: tests) {
				if (!test.run()) {
					std::cout << "Test suite failed: " << test.name << std::endl;
					return false;
				};
			}
			if (afterCallback) {
				afterCallback();
			}
		} catch (const AssertException& e) {
			return false;
		}
		std::cout << "All tests in the block \"" << name
							<< "\" passed successfully!" << std::endl;
		return true;
	}


	void setBeforeCallback(const std::function<void()>& callback) {
		beforeCallback = callback;
	}


	void setBlockCallback(const std::function<void()>& callback) {
		blockCallback = callback;
	}

	void addTest(const Test& test) {
		tests.push_back(test);
	}


	void setAfterCallback(const std::function<void()>& callback) {
		afterCallback = callback;
	}

private:
	std::string name {};
	std::function<void()> beforeCallback {};
	std::function<void()> blockCallback {};
	std::function<void()> afterCallback {};
	std::list<Test> tests;
};

#define describe(desc, cb) { \
  TestBlock block{desc};      \
  block.setBlockCallback([&]() -> void cb);  \
}

#define beforeAll(cb) { \
  block.setBeforeCallback([&]() -> void cb); \
}

#define afterAll(cb) { \
  block.setAfterCallback([&]() -> void cb);  \
}

#define test(name, cb) { \
  block.addTest(Test{name, [&]() -> void cb});  \
}

#endif //ARDUI_TESTBLOCK_H
