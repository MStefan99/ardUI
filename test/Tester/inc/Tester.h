//
// Created by MStefan99 on 17.3.21.
//

#ifndef ARDUI_TESTER_H
#define ARDUI_TESTER_H


/*
 * Deferred run
 * Adds all the tests in the queue and runs them once all tests have been added.
 * May cause local variables to be deallocated.
 *
 * Suite setup and teardown are only available with deferred run enabled.
 */
#define DEFERRED_RUN ( true )


#include <string>
#include <functional>

#include "TestBlock.h"


void describe(const std::string& desc,
		const std::function<void(TestBlock&)>& callback);


#endif //ARDUI_TESTER_H
