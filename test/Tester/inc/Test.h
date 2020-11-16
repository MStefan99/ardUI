//
// Created by MStefan99 on 16.11.20.
//

#ifndef ARDUI_TEST_H
#define ARDUI_TEST_H


#include <functional>

#include "AssertException.h"
#include "Matcher.h"


class Test {
public:
	Test() = delete;

	explicit Test(const std::string& name, const std::function<void()>& callback):
			name {name},
			callback {callback} {}

	bool run() const {
		try {
			callback();
		} catch (const AssertException& e) {
			std::cout << "Test failed: " << e.what() << std::endl;
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
