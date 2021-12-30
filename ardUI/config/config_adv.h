//
// Created by MStefan99 on 8.7.21.
//

#ifndef ARDUI_CONFIG_ADV_H
#define ARDUI_CONFIG_ADV_H


/*
 * Use standard template library.
 * Disable if not supported on your platform.
 */
#define USE_STL ( true )


/*
 * Smart delay prevents ardUI from pausing whenever you call the
 * delay() function, so that the UI always remains dynamic and responsive.
 * If this feature is disabled, no UI updates will happen during sleep(),
 * which means all UI interactions will be paused as well.
 */
#define SMART_DELAY ( true )


/*
 * Enable debug mode.
 * Can be useful during debugging.
 * Debug mode is not guaranteed to run on Arduino
 * and will only be turned on in a desktop environment.
 */
#define DEBUGGING ( true )


/*
 * Introduces delay between loop iterations.
 * Can reduce the CPU load by only running the loop once per update.
 * Does not affect UI performance but leaves less time for other operations.
 */
#define SLOW_MODE ( false )

/*
 * Enable Display fallback.
 * This is a utility for drawing using fallback shapes.
 * Enable it if your display library does not support some shapes that ardUI uses.
 */
#define DISPLAY_FALLBACK ( false )

#endif //ARDUI_CONFIG_ADV_H
