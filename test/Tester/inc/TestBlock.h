//
// Created by MStefan99 on 16.11.20.
//

#ifndef ARDUI_TESTBLOCK_H
#define ARDUI_TESTBLOCK_H


#include <functional>
#include <list>

#include "AssertException.h"
#include "Test.h"
#include "Terminal.h"


class TestBlock {
public:
	TestBlock() = default;


	TestBlock(const std::string& name, const std::function<void(TestBlock&)>& cb):
		name {name}, blockCallback {cb} {
		#if !DEFERRED_RUN
		std::cout << BLUE << "Running suite \"" + name + "\"..." << NC << std::endl;
		runBefore();
		#endif
	}


	~TestBlock() {
		run();
		#if !DEFERRED_RUN
		runAfter();
		printResults();
		#endif
	}


	#if DEFERRED_RUN
	void beforeAll(const std::function<void()>& callback) {
		beforeCallback = callback;
	}


	void afterAll(const std::function<void()>& callback) {
		afterCallback = callback;
	}
	#endif


	void test(const std::string& testName, const std::function<void()>& cb) {
		#if DEFERRED_RUN
		tests.emplace_back(testName, cb);
		#else
		runTest({testName, cb});
		#endif
	}


protected:
	std::string name {};
	std::function<void()> beforeCallback {};
	std::function<void(TestBlock&)> blockCallback {};
	std::function<void()> afterCallback {};
	bool passed = true;
	#if DEFERRED_RUN
	std::list<Test> tests;
	#endif


	void runBefore() {
		try {
			blockCallback(*this);
			if (beforeCallback) {
				beforeCallback();
				std::cout << GREEN << "Suite setup passed" << NC << std::endl;
			}
		} catch (const AssertException& e) {
			passed = false;
		}
	}


	void runAfter() {
		try {
			if (afterCallback) {
				afterCallback();
				std::cout << GREEN << "Suite teardown passed" << NC << std::endl;
			}
		} catch (const AssertException& e) {
			passed = false;
		}
	}


	void runTest(const Test& test) {
		try {
			if (!test.run()) {
				passed = false;
			}
		} catch (const AssertException& e) {
			passed = false;
		}
	}


	void printResults() {
		if (passed) {
			std::cout << GREEN << "All tests in the suite \"" << name
								<< "\" passed successfully!" << NC << std::endl;
		} else {
			std::cout << RED << "Test suite \"" << name << "\" failed." << NC << std::endl;
		}
	}


	void run() {
		#if DEFERRED_RUN
		runBefore();
		for (const auto& test: tests) {
			runTest(test);
		}
		runAfter();
		printResults();
		#endif
	}
};

#endif //ARDUI_TESTBLOCK_H
