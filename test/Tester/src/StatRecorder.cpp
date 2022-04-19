//
// Created by MStefan99 on 13.7.21.
//

#include "StatRecorder.hpp"


size_t StatRecorder::_totalSuites {};
size_t StatRecorder::_passedSuites {};
size_t StatRecorder::_totalTests {};
size_t StatRecorder::_ranTests {};
size_t StatRecorder::_passedTests {};
auto StatRecorder::_startTime {std::chrono::system_clock::now()};


StatRecorder::~StatRecorder() {
	auto now {std::chrono::system_clock::now()};

	std::cout << std::endl;
	std::cout << BOLD << "Test suites: " << RST;
	if (_totalSuites != _passedSuites) {
		std::cout << FG_RED << _totalSuites - _passedSuites << " failed, " << RST;
	}
	std::cout << FG_GREEN << _passedSuites << " passed, " << RST;
	std::cout << _totalSuites << " total." << std::endl;

	std::cout << BOLD << "Test cases:  " << RST;
	if (_totalTests != _ranTests) {
		std::cout << FG_RED << _ranTests << " ran, " << RST;
	}
	if (_ranTests != _passedTests) {
		std::cout << FG_RED << _ranTests - _passedTests << " failed, " << RST;
	}
	std::cout << FG_GREEN << _passedTests << " passed, " << RST;
	std::cout << _totalTests << " total." << std::endl;

	std::cout << BOLD << "Time taken:  " << RST << std::fixed << std::setprecision(4)
						<< (now - _startTime).count() / 1000000000.0 << "s" << std::endl;

	std::cout << std::endl;

	exit(_totalSuites - _passedSuites);
}
