//
// Created by MStefan99 on 16.11.20.
//

#ifndef ARDUI_TESTSUITE_H
#define ARDUI_TESTSUITE_H

#include <functional>
#include <list>
#include <sstream>

#include "AssertException.h"
#include "Tester_options.h"
#include "StatRecorder.h"
#include "Test.h"
#include "Terminal.h"


class TestSuite {
public:
	TestSuite();
	TestSuite(const std::string& name,
			const std::function<void(TestSuite&)>& callback);

	~TestSuite();

	#if DEFERRED_RUN
	void beforeAll(const std::function<void()>& callback);
	void afterAll(const std::function<void()>& callback);

	void beforeEach(const std::function<void()>& callback);
	void afterEach(const std::function<void()>& callback);
	#endif

	void test(const std::string& testName,
			const std::function<void()>& callback);

protected:
	void runBefore();
	void runAfter();
	void runTest(const Test& test);
	void printResults() const;
	void run();

	std::string _name {};
	std::function<void()> _beforeAllCb {};
	std::function<void()> _beforeEachCb {};
	std::function<void(TestSuite&)> _blockCb {};
	std::function<void()> _afterAllCb {};
	std::function<void()> _afterEachCb {};
	std::list<std::pair<std::string, std::string>> _errors {};
	bool _passed {true};
	#if DEFERRED_RUN
	std::list<Test> _tests {};
	#endif
};

#endif //ARDUI_TESTSUITE_H
