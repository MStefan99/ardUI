//
// Created by MStefan99 on 13.7.21.
//

#ifndef ARDUI_TESTCOUNTER_H
#define ARDUI_TESTCOUNTER_H

#include <iostream>

#include "Terminal.h"
#include "Singleton.h"


class TestCounter: public Singleton<TestCounter> {
public:
	~TestCounter();

	friend class TestSuite;

	friend class Test;

protected:
	static size_t _totalSuites;
	static size_t _passedSuites;
	static size_t _totalTests;
	static size_t _ranTests;
	static size_t _passedTests;
};

#endif //ARDUI_TESTCOUNTER_H
