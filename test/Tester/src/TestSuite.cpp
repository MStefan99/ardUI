//
// Created by MStefan99 on 13.7.21.
//

#include "TestSuite.hpp"


TestSuite::TestSuite() {
	StatRecorder::getInstance();
	++StatRecorder::_totalSuites;
}


TestSuite::TestSuite(const std::string& name, const std::function<void(TestSuite&)>& cb):
		_name {name}, _blockCb {cb} {
	StatRecorder::getInstance();
	++StatRecorder::_totalSuites;
	#if !TESTER_DEFERRED_RUN
	runBefore();
	#endif
}


TestSuite::~TestSuite() {
	run();
	#if !TESTER_DEFERRED_RUN
	runAfter();
	printResults();
	#endif
}


#if TESTER_DEFERRED_RUN


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
	#if TESTER_DEFERRED_RUN
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
			_passed.emplace_back("Suite setup");
		}
	} catch (const AssertException& e) {
		_failed.emplace_back("Suite setup", e.what());
	}
}


void TestSuite::runAfter() {
	try {
		if (_afterAllCb) {
			_afterAllCb();
			_passed.emplace_back("Suite teardown");
		}
	} catch (const AssertException& e) {
		_failed.emplace_back("Suite teardown", e.what());
	}
}


void TestSuite::runTest(const Test& test) {
	try {
		if (_beforeEachCb) {
			_beforeEachCb();
			_passed.emplace_back(test.getName() + " > Test setup");
		}
	} catch (const AssertException& e) {
		_failed.emplace_back(test.getName() + " > Test setup", e.what());
	}
	if (_failed.empty() || !TESTER_STOP_ON_FAIL) {
		try {
			test.run();
			_passed.emplace_back(test.getName());
		} catch (const AssertException& e) {
			_failed.emplace_back(test.getName(), e.what());
		}
	}
	try {
		if (_afterEachCb) {
			_afterEachCb();
			_passed.emplace_back(test.getName() + " > Test teardown");
		}
	} catch (const AssertException& e) {
		_failed.emplace_back(test.getName() + " > Test teardown", e.what());
	}
}


void TestSuite::printResults() const {
	if (_failed.empty()) {
		std::cout << BG_BRIGHT_GREEN << FG_BLACK << " PASS " << RST << " " << _name << std::endl;
	} else {
		std::cout << BG_BRIGHT_RED << FG_BLACK << " FAIL " << RST << " " << _name << RST << std::endl;
	}
	#if TESTER_PRINT_PASSED
	for (const auto& e : _passed) {
		std::cout << FG_GREEN << "  ● " << e << RST << std::endl;
	}
	std::cout << std::endl;
	#endif
	for (const auto& e : _failed) {
		std::cout << FG_RED << "  ● " << e.first << RST << std::endl
							<< e.second << std::endl << std::endl;
	}
}


void TestSuite::run() {
	#if TESTER_DEFERRED_RUN
	runBefore();
	if (_failed.empty()) {
		for (const auto& test : _tests) {
			runTest(test);
		}
	}
	runAfter();
	printResults();
	#endif
	if (_failed.empty()) {
		++StatRecorder::_passedSuites;
	}
}