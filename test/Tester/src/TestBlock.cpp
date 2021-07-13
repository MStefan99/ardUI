//
// Created by MStefan99 on 13.7.21.
//

#include "TestBlock.h"


TestBlock::TestBlock() {
	TestCounter::getInstance();
	++TestCounter::_totalSuites;
}


TestBlock::TestBlock(const std::string& name, const std::function<void(TestBlock&)>& cb):
		_name {name}, _blockCallback {cb} {
	TestCounter::getInstance();
	++TestCounter::_totalSuites;
	#if !DEFERRED_RUN
	std::cout << BG_BLUE << " RUN " << RST << " " << name << '\r';
	runBefore();
	#endif
}


TestBlock::~TestBlock() {
	run();
	#if !DEFERRED_RUN
	runAfter();
	printResults();
	#endif
}


#if DEFERRED_RUN


void TestBlock::beforeAll(const std::function<void()>& cb) {
	_beforeCallback = cb;
}


void TestBlock::afterAll(const std::function<void()>& cb) {
	_afterCallback = cb;
}


#endif


void TestBlock::test(const std::string& testName,
		const std::function<void()>& cb) {
	#if DEFERRED_RUN
	_tests.emplace_back(testName, cb);
	#else
	runTest({testName, cb});
	#endif
}


void TestBlock::runBefore() {
	try {
		_blockCallback(*this);
		if (_beforeCallback) {
			_beforeCallback();
		}
	} catch (const AssertException& e) {
		_passed = false;
	}
}


void TestBlock::runAfter() {
	try {
		if (_afterCallback) {
			_afterCallback();
		}
	} catch (const AssertException& e) {
		_passed = false;
	}
}


void TestBlock::runTest(const Test& test) {
	try {
		test.run();
	} catch (const AssertException& e) {
		_errors.emplace_back(test, e.what());
		_passed = false;
	}
}


void TestBlock::printResults() const {
	if (_passed) {
		std::cout << BG_GREEN << FG_BLACK << " PASS " << RST << " " << _name << std::endl;
	} else {
		std::cout << BG_RED << FG_BLACK << " FAIL " << RST << " " << _name << RST << std::endl;
		for (const auto& e: _errors) {
			std::cout << FG_RED << "● " << e.first.getName() << RST << std::endl
			<< e.second << std::endl << std::endl;
		}
	}
}


void TestBlock::run() {
	#if DEFERRED_RUN
	runBefore();
	for (const auto& test: _tests) {
		runTest(test);
	}
	runAfter();
	printResults();
	if (_passed) {
		++TestCounter::_passedSuites;
	}
	#endif
}