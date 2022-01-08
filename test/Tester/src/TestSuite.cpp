//
// Created by MStefan99 on 13.7.21.
//

#include "TestSuite.h"


TestSuite::TestSuite() {
	StatRecorder::getInstance();
	++StatRecorder::_totalSuites;
}


TestSuite::TestSuite(const std::string& name, const std::function<void(TestSuite&)>& cb):
		_name {name}, _blockCb {cb} {
	StatRecorder::getInstance();
	++StatRecorder::_totalSuites;
	#if !DEFERRED_RUN
	runBefore();
	#endif
}


TestSuite::~TestSuite() {
	run();
	#if !DEFERRED_RUN
	runAfter();
	printResults();
	#endif
}


#if DEFERRED_RUN


void TestSuite::beforeAll(const std::function<void()>& cb) {
	_beforeAllCb = cb;
}


void TestSuite::afterAll(const std::function<void()>& cb) {
	_afterAllCb = cb;
}


void TestSuite::beforeEach(const std::function<void()>& cb) {
	_beforeEachCb = cb;
}


void TestSuite::afterEach(const std::function<void()>& cb) {
	_afterEachCb = cb;
}


#endif


void TestSuite::test(const std::string& testName,
		const std::function<void()>& cb) {
	#if DEFERRED_RUN
	_tests.emplace_back(testName, cb);
	#else
	runTest({testName, cb});
	#endif
}


void TestSuite::runBefore() {
	try {
		_blockCb(*this);
		if (_beforeAllCb) {
			_beforeAllCb();
		}
	} catch (const AssertException& e) {
		_errors.emplace_back("Suite setup", e.what());
		_passed = false;
	}
}


void TestSuite::runAfter() {
	try {
		if (_afterAllCb) {
			_afterAllCb();
		}
	} catch (const AssertException& e) {
		_errors.emplace_back("Suite teardown", e.what());
		_passed = false;
	}
}


void TestSuite::runTest(const Test& test) {
	try {
		if (_beforeEachCb) {
			_beforeEachCb();
		}
	} catch (const AssertException& e) {
		_errors.emplace_back(test.getName() + " > Test setup", e.what());
		_passed = false;
	}
	if (_passed || !STOP_ON_FAIL) {
		try {
			test.run();
		} catch (const AssertException& e) {
			_errors.emplace_back(test.getName(), e.what());
			_passed = false;
		}
	}
	try {
		if (_afterEachCb) {
			_afterEachCb();
		}
	} catch (const AssertException& e) {
		_errors.emplace_back(test.getName() + " > Test teardown", e.what());
		_passed = false;
	}
}


void TestSuite::printResults() const {
	if (_passed) {
		std::cout << BG_BRIGHT_GREEN << FG_BLACK << " PASS " << RST << " " << _name << std::endl;
	} else {
		std::cout << BG_BRIGHT_RED << FG_BLACK << " FAIL " << RST << " " << _name << RST << std::endl;
		for (const auto& e: _errors) {
			std::cout << FG_RED << "● " << e.first << RST << std::endl
			          << e.second << std::endl << std::endl;
		}
	}
}


void TestSuite::run() {
	#if DEFERRED_RUN
	runBefore();
	if (_passed) {
		for (const auto& test: _tests) {
			runTest(test);
		}
	}
	runAfter();
	printResults();
	#endif
	if (_passed) {
		++StatRecorder::_passedSuites;
	}
}