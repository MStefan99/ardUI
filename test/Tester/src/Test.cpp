//
// Created by MStefan99 on 13.7.21.
//

#include "Test.h"


Test::Test() {
	++TestCounter::_totalTests;
}


Test::Test(std::string name, std::function<void()> callback):
		_name {std::move(name)},
		_callback {std::move(callback)} {
	++TestCounter::_totalTests;
}


void Test::run() const {
	if (_callback) {
		try {
			_callback();
			++TestCounter::_passedTests;
		} catch (const AssertException& e) {
			throw e;
		}
	}
}


const std::string& Test::getName() const {
	return _name;
}
