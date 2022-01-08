//
// Created by MStefan99 on 13.7.21.
//

#ifndef ARDUI_OPTIONS_H
#define ARDUI_OPTIONS_H

/*
 * Deferred run
 * Adds all the tests in the queue and runs them once all tests have been added.
 * May cause local variables to be deallocated.
 *
 * Suite setup and teardown are only available with deferred run enabled.
 */
#define DEFERRED_RUN ( true )


/*
 * Stop on fail
 * Stops suite execution immediately if a test case fails.
 */
#define STOP_ON_FAIL ( true )

#endif //ARDUI_OPTIONS_H
