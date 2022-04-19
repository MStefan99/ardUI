//
// Created by MStefan99 on 13.7.21.
//

#ifndef ARDUI_TESTER_OPTIONS_HPP
#define ARDUI_TESTER_OPTIONS_HPP

/*
 * Deferred run
 * Adds all the tests in the queue and runs them once all tests have been added.
 * Will cause local variables to be deallocated.
 *
 * Suite setup and teardown are only available with deferred run enabled.
 */
#define TESTER_DEFERRED_RUN ( true )


/*
 * Stop on fail
 * Stops suite execution immediately if a test case fails.
 */
#define TESTER_STOP_ON_FAIL ( true )


/*
 * Print passed tests
 * Will output all passed tests to the console.
 */
#define TESTER_PRINT_PASSED ( false )

#endif //ARDUI_TESTER_OPTIONS_HPP
