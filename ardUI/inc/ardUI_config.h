//
// Created by MStefan99 on 17.12.19.
//

#ifndef ARDUI_CONFIG_H
#define ARDUI_CONFIG_H


#include <Arduino.h>

/*
 * How many back actions to save.
 * Higher values improve user experience but require more RAM.
 */
#define BACK_STACK_DEPTH ( 3 )
/*
 * Use standard template library.
 * Disable if not supported on your platform.
 */
#define USE_STL ( false )

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
 * Enter the values in px since last touch refresh.
 */
#define SCROLL_SENSITIVITY ( 10 )

#ifndef Arduino_h
#define DEBUG
#endif

#endif //ARDUI_CONFIG_H