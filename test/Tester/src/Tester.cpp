//
// Created by MStefan99 on 13.7.21.
//

#include "Tester.h"


void describe(const std::string& desc, const std::function<void(TestBlock&)>& cb) {
	TestBlock block {desc, cb};
}
