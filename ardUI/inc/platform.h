//
// Created by MStefan99 on 22.1.20.
//

#ifndef ARDUI_PLATFORM_H
#define ARDUI_PLATFORM_H


#include <Arduino.h>
#include "ardUI_config.h"


#if USE_STL

	#define LESS_H <functional>
	#define PAIR_H <utility>
	#define VECTOR_H <vector>
	#define LIST_H <list>
	#define MAP_H <map>
	#define STACK_H <stack>
	#define QUEUE_H <queue>

	#define NAMESPACE std

#else

	#define LESS_H "less.h"
	#define PAIR_H "pair.h"
	#define VECTOR_H "vector.h"
	#define LIST_H "list.h"
	#define MAP_H "map.h"
	#define STACK_H "stack.h"
	#define QUEUE_H "queue.h"

	#define NAMESPACE ardui

#endif

#define PAIR NAMESPACE::pair
#define VECTOR NAMESPACE::vector
#define LIST NAMESPACE::list
#define LESS NAMESPACE::less
#define MAP NAMESPACE::map
#define STACK NAMESPACE::stack
#define QUEUE NAMESPACE::queue

#if (!defined(Arduino_h) && ENABLE_DEBUG)
	#define DEBUG
#endif

#endif //ARDUI_PLATFORM_H
