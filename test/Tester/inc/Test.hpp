//
// Created by MStefan99 on 16.11.20.
//

#ifndef ARDUI_TEST_HPP
#define ARDUI_TEST_HPP

#include <functional>
#include <iostream>
#include <utility>

#include "AssertException.hpp"
#include "Tester_options.hpp"
#include "StatRecorder.hpp"
#include "Matcher.hpp"
#include "Terminal.hpp"


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

#endif //ARDUI_TEST_HPP
