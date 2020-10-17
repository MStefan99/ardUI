//
// Created by MStefan99 on 22.1.20.
//

#ifndef ARDUI_PLATFORM_H
#define ARDUI_PLATFORM_H


#include "ardUI_config.h"
#include <Arduino.h>


#if USE_STL


#include <vector>
#include <list>
#include <map>


#define VECTOR std::vector
#define LIST std::list
#define LESS std::less
#define MAP std::map
#define STACK std::stack
#define QUEUE std::queue

#else


#include "vector.h"
#include "list.h"
#include "map.h"


#define VECTOR ardui::vector
#define LIST ardui::list
#define LESS ardui::less
#define MAP ardui::map
#define STACK ardui::stack
#define QUEUE ardui::queue

#endif

#endif //ARDUI_PLATFORM_H
