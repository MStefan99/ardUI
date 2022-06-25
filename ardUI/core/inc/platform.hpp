//
// Created by MStefan99 on 22.1.20.
//

#ifndef ARDUI_PLATFORM_HPP
#define ARDUI_PLATFORM_HPP

#include <Arduino.h>
#include "config.hpp"
#include "config_adv.hpp"


#ifndef __EMSCRIPTEN__
	#define S_PUBLIC public
	#define S_PROTECTED protected
	#define S_PRIVATE private
#else
	#define S_PUBLIC public
	#define S_PROTECTED public
	#define S_PRIVATE public
#endif


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
	#define DISPLAY_H "DisplayController.hpp"
	#define DISPLAY_UTIL DisplayController
#else
	#define DISPLAY_H "display.hpp"
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

	#define LESS_H "less.hpp"
	#define PAIR_H "pair.hpp"
	#define VECTOR_H "vector.hpp"
	#define LIST_H "list.hpp"
	#define MAP_H "map.hpp"
	#define STACK_H "stack.hpp"
	#define QUEUE_H "queue.hpp"

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

#endif //ARDUI_PLATFORM_HPP
