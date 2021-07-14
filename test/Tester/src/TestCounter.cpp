//
// Created by MStefan99 on 13.7.21.
//

#include "TestCounter.h"


size_t TestCounter::_totalSuites {};
size_t TestCounter::_passedSuites {};
size_t TestCounter::_totalTests {};
size_t TestCounter::_ranTests {};
size_t TestCounter::_passedTests {};


TestCounter::~TestCounter() {
	std::cout << std::endl << BOLD << "Test suites: " << RST;
	if (_totalSuites != _passedSuites) {
		std::cout << FG_RED << _totalSuites - _passedSuites << " failed, " << RST;
	}
	std::cout << FG_GREEN << _passedSuites << " passed, " << RST;
	std::cout << _totalSuites << " total.";

	std::cout << std::endl << BOLD << "Test cases:  " << RST;
	if (_totalTests != _ranTests) {
		std::cout << FG_RED << _ranTests << " ran, " << RST;
	} else if (_totalTests != _passedTests) {
		std::cout << FG_RED << _totalTests - _passedTests << " failed, " << RST;
	}
	std::cout << FG_GREEN << _passedTests << " passed, " << RST;
	std::cout << _totalTests << " total.";

	std::cout << std::endl << std::endl;

	exit(_totalSuites - _passedSuites);
}
