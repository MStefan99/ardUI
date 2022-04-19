//
// Created by MStefan99 on 13.7.21.
//

#include "Test.hpp"


Test::Test() {
	++StatRecorder::_totalTests;
}


Test::Test(std::string name, std::function<void()> callback):
		_name {std::move(name)},
		_callback {std::move(callback)} {
	++StatRecorder::_totalTests;
}


void Test::run() const {
	++StatRecorder::_ranTests;
	if (_callback) {
		try {
			_callback();
			++StatRecorder::_passedTests;
		} catch (const AssertException& e) {
			throw e;
		}
	}
}


const std::string& Test::getName() const {
	return _name;
}
