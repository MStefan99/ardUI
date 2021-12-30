//
// Created by MStefan99 on 22.1.20.
//

#ifndef ARDUI_PLATFORM_H
#define ARDUI_PLATFORM_H

#include <Arduino.h>
#include "config.h"
#include "config_adv.h"


#if LOG_LEVEL < LOG_NONE || LOG_LEVEL > LOG_VERBOSE
#error ERROR: Invalid log level
#endif

#if COLOR_MODE != COLOR_888 && COLOR_MODE != COLOR_565
#error ERROR: Invalid color mode
#endif

#if REFRESH_RATE <= 0 || TOUCH_RATE <= 0
#error ERROR: Refresh rate should be greater than zero
#endif

#if DISPLAY_FALLBACK
	#define DISPLAY_H "DisplayController.h"
	#define DISPLAY_UTIL DisplayController
#else
	#define DISPLAY_H "display.h"
	#define DISPLAY_UTIL ardui::display
#endif

#define CTL_NS tl

#if USE_STL

	#define LESS_H <functional>
	#define PAIR_H <utility>
	#define VECTOR_H <vector>
	#define LIST_H <list>
	#define MAP_H <map>
	#define STACK_H <stack>
	#define QUEUE_H <queue>

	#define TL_NS std

#else

	#define LESS_H "less.h"
	#define PAIR_H "pair.h"
	#define VECTOR_H "vector.h"
	#define LIST_H "list.h"
	#define MAP_H "map.h"
	#define STACK_H "stack.h"
	#define QUEUE_H "queue.h"

	#define TL_NS CTL_NS

#endif


#define ABS(a) ((a > 0)? (a) : -(a))
#define MIN(a, b) ((a < b)? (a) : (b))
#define MAX(a, b) ((a > b)? (a) : (b))
#define SWAP(a, b) {\
  auto t {a};  \
  a = b;  \
  b = t;\
}

#if !defined(Arduino_h) && DEBUGGING
	#define DEBUG_MODE ( true )
#else
	#define DEBUG_MODE ( false )
#endif

#endif //ARDUI_PLATFORM_H
