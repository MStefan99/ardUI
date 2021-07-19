//
// Created by MStefan99 on 13.7.21.
//

#ifndef ARDUI_STATRECORDER_H
#define ARDUI_STATRECORDER_H

#include <iostream>
#include <chrono>
#include <iomanip>

#include "Terminal.h"
#include "Singleton.h"


class StatRecorder: public Singleton<StatRecorder> {
public:
	~StatRecorder();

	friend class TestSuite;

	friend class Test;

protected:
	static size_t _totalSuites;
	static size_t _passedSuites;
	static size_t _totalTests;
	static size_t _ranTests;
	static size_t _passedTests;
	static std::chrono::time_point<std::chrono::system_clock> _startTime;
};

#endif //ARDUI_STATRECORDER_H
