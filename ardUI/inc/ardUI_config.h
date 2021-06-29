//
// Created by MStefan99 on 17.12.19.
//

#ifndef ARDUI_CONFIG_H
#define ARDUI_CONFIG_H

#include <Arduino.h>


// Platform
/*
 * Use standard template library.
 * Disable if not supported on your platform.
 */
#define USE_STL ( true )


// User Interface
/*
 * How many previous activities to save.
 * If a new activity is opened while previous one is still active,
 * it will be saved to memory so that the user can navigate back to it.
 * Higher values improve user experience but will use significantly more memory.
 */
#define BACK_STACK_DEPTH ( 3 )

/*
 * How often to update a display.
 * Higher values result in a smoother image
 * but may impact your main program performance.
 *
 * Enter the value in Hz.
 */
#define REFRESH_RATE ( 10 )

/*
 * How often to check for user input.
 * Higher values result in a more accurate and responsive touch
 * input at a small performance drop.
 *
 * Enter the value in Hz.
 */
#define TOUCH_RATE ( 60 )

/*
 * Hybrid sleep prevents ardUI from pausing whenever you call the
 * delay() function, so that the UI always remains dynamic and responsive.
 * If this feature is disabled, no UI updates will happen during sleep(),
 * which means all UI interactions will be paused as well.
 */
#define SMART_DELAY ( true )

/*
 * How long to wait for a long click.
 * The higher the value, the longer the user has to touch and
 * hold the screen to trigger a long click.
 *
 * Enter the value in ms.
 */
#define LONG_CLICK_TIME ( 300 )

/*
 * How fast should the user scroll.
 * The higher the value, the faster the user has to scroll to
 * switch into the scrolling mode.
 *
 * Enter the values in px/s.
 */
#define SCROLL_SENSITIVITY ( 50 )


// Debugging
/*
 * Enable debug mode.
 * Can be useful during debugging.
 * Debug mode is not guaranteed to run on Arduino
 * and will only turned on in a desktop environment.
 */
#define DEBUGGING ( true )

/*
 * Enable verbose logging.
 * Verbose logging may be useful for debugging
 * but may impact performance with slow serial connections.
 */
#define VERBOSE ( true )
// TODO: add log levels

/*
 * Introduces delays between loop iterations.
 * Can reduce the CPU load by only running the loop once per update.
 * Does not affect UI performance but leaves less time for other operations.
 */
#define SLOW_MODE ( false )

#endif //ARDUI_CONFIG_H
