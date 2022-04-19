//
// Created by MStefan99 on 17.3.21.
//

#ifndef ARDUI_TESTER_HPP
#define ARDUI_TESTER_HPP

#include <string>
#include <functional>

#include "TestSuite.hpp"
#include "Tester_options.hpp"


void describe(const std::string& desc,
		const std::function<void(TestSuite&)>& callback);


void test(const std::string& desc,
		const std::function<void()>& callback);

#endif //ARDUI_TESTER_HPP
