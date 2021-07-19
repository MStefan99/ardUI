//
// Created by MStefan99 on 17.12.19.
//

#ifndef ARDUI_CONFIG_H
#define ARDUI_CONFIG_H

#include "definitions.h"


/*
 * How many previous Activities to save.
 * If a new activity is opened while previous one is still active,
 * it will be saved to memory so that the user can navigate back to it.
 * Higher values improve user experience but will use significantly more memory.
 */
#define BACK_STACK_DEPTH ( 1 )


/*
 * How often to update a display.
 * Higher values result in a smoother image
 * but may heavily impact performance.
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
 * Enter the values in px/s.
 */
#define SCROLL_SENSITIVITY ( 50 )


/*
 * Enable verbose logging.
 * Verbose logging may be useful for debugging
 * but may impact performance with slow serial connections.
 */
#define LOG_LEVEL ( LOG_ERROR )


/*
 * Color mode.
 * You can choose whether to use 24 or 16-bit colors.
 * If your display doesn't support 24-bit colors, choose 16-bit mode to save memory.
 */
#define COLOR_MODE ( COLOR_565 )

#endif //ARDUI_CONFIG_H
