//
// Created by MStefan99 on 13.7.21.
//

#ifndef ARDUI_STATRECORDER_HPP
#define ARDUI_STATRECORDER_HPP

#include <iostream>
#include <chrono>
#include <iomanip>

#include "Terminal.hpp"
#include "Singleton.hpp"


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

#endif //ARDUI_STATRECORDER_HPP
