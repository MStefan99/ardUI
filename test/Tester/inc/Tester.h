//
// Created by MStefan99 on 17.3.21.
//

#ifndef ARDUI_TESTER_H
#define ARDUI_TESTER_H

#include <string>
#include <functional>

#include "TestSuite.h"
#include "Tester_options.h"


void describe(const std::string& desc,
		const std::function<void(TestSuite&)>& callback);


void test(const std::string& desc,
		const std::function<void()>& callback);

#endif //ARDUI_TESTER_H
