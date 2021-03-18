//
// Created by MStefan99 on 16.11.20.
//

#ifndef ARDUI_TEST_H
#define ARDUI_TEST_H


#include <functional>
#include <iostream>

#include "AssertException.h"
#include "Matcher.h"
#include "Terminal.h"


class Test {
public:
	Test() = delete;


	Test(const std::string& name, const std::function<void()>& callback):
		name {name},
		callback {callback} {}


	bool run() const {
		try {
			callback();
			std::cout << GREEN << "Test passed: " << name << NC << std::endl;
		} catch (const AssertException& e) {
			std::cout << RED << "Test failed: " << name << ". " << e.what() << std::endl;
			return false;
		}
		return true;
	};

	friend class TestBlock;

private:
	std::string name {};
	std::function<void()> callback {};
};

#endif //ARDUI_TEST_H
