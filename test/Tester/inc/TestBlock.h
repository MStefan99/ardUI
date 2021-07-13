//
// Created by MStefan99 on 16.11.20.
//

#ifndef ARDUI_TESTBLOCK_H
#define ARDUI_TESTBLOCK_H

#include <functional>
#include <list>
#include <sstream>

#include "AssertException.h"
#include "Test.h"
#include "Terminal.h"


class TestBlock {
public:
	TestBlock() = default;
	TestBlock(const std::string& name,
			const std::function<void(TestBlock&)>& callback);

	~TestBlock();

	#if DEFERRED_RUN
	void beforeAll(const std::function<void()>& callback);

	void afterAll(const std::function<void()>& callback);
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
	std::function<void()> _beforeCallback {};
	std::function<void(TestBlock&)> _blockCallback {};
	std::function<void()> _afterCallback {};
	std::ostringstream _errors {};
	bool _passed = true;
	#if DEFERRED_RUN
	std::list<Test> _tests {};
	#endif
};

#endif //ARDUI_TESTBLOCK_H
