//
// Created by MStefan99 on 13.7.21.
//

#include "Test.h"


Test::Test(std::string name, std::function<void()> callback):
		_name {std::move(name)},
		_callback {std::move(callback)} {}


void Test::run() const {
	_callback();
}
