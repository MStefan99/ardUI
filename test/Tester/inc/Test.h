//
// Created by MStefan99 on 16.11.20.
//

#ifndef ARDUI_TEST_H
#define ARDUI_TEST_H

#include <functional>
#include <iostream>
#include <utility>

#include "AssertException.h"
#include "Matcher.h"
#include "Terminal.h"


class Test {
public:
	Test() = delete;
	Test(std::string name, std::function<void()> callback);

	void run() const;

private:
	std::string _name {};
	std::function<void()> _callback {};
};

#endif //ARDUI_TEST_H
