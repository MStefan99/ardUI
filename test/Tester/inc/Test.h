//
// Created by MStefan99 on 16.11.20.
//

#ifndef ARDUI_TEST_H
#define ARDUI_TEST_H

#include <functional>
#include <iostream>
#include <utility>

#include "AssertException.h"
#include "Tester_options.h"
#include "TestCounter.h"
#include "Matcher.h"
#include "Terminal.h"


class Test {
public:
	Test();
	Test(std::string name, std::function<void()> callback);

	void run() const;
	const std::string& getName() const;

private:
	std::string _name {};
private:
	std::function<void()> _callback {};
};

#endif //ARDUI_TEST_H
