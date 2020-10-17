//
// Created by MStefan99 on 22.1.20.
//

#ifndef ARDUI_PLATFORM_H
#define ARDUI_PLATFORM_H


#include "ardUI_config.h"
#include <Arduino.h>


#if USE_STL

#define VECTOR_H <vector>
#define LIST_H <list>
#define LESS_H <less>
#define MAP_H <map>
#define STACK_H <stack>
#define QUEUE_H <queue>

#define VECTOR std::vector
#define LIST std::list
#define LESS std::less
#define MAP std::map
#define STACK std::stack
#define QUEUE std::queue

#else

#define VECTOR_H "vector.h"
#define LIST_H "list.h"
#define LESS_H "less.h"
#define MAP_H "map.h"
#define STACK_H "stack.h"
#define QUEUE_H "queue.h"

#define VECTOR ardui::vector
#define LIST ardui::list
#define LESS ardui::less
#define MAP ardui::map
#define STACK ardui::stack
#define QUEUE ardui::queue

#endif

#endif //ARDUI_PLATFORM_H
