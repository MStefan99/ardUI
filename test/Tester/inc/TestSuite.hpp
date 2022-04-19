//
// Created by MStefan99 on 16.11.20.
//

#ifndef ARDUI_TESTSUITE_HPP
#define ARDUI_TESTSUITE_HPP

#include <functional>
#include <list>
#include <sstream>

#include "AssertException.hpp"
#include "Tester_options.hpp"
#include "StatRecorder.hpp"
#include "Test.hpp"
#include "Terminal.hpp"


class TestSuite {
public:
	TestSuite();
	TestSuite(const std::string& name,
			const std::function<void(TestSuite&)>& callback);

	~TestSuite();

	#if TESTER_DEFERRED_RUN
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
	std::function<void(TestSuite&)> _blockCb {};

	std::function<void()> _beforeAllCb {};
	std::function<void()> _beforeEachCb {};
	std::function<void()> _afterAllCb {};
	std::function<void()> _afterEachCb {};

	std::list<std::string> _passed {};
	std::list<std::pair<std::string, std::string>> _failed {};

	#if TESTER_DEFERRED_RUN
	std::list<Test> _tests {};
	#endif
};

#endif //ARDUI_TESTSUITE_HPP
