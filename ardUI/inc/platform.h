//
// Created by MStefan99 on 22.1.20.
//

#ifndef ARDUI_PLATFORM_H
#define ARDUI_PLATFORM_H


#include "ardUI_config.h"

#include <Arduino.h>


#if USING_STL
#include <vector>
#include <list>
#include <map>

#else
#include "vector.h"
#include "list.h"
#include "map.h"

#endif

#endif //ARDUI_PLATFORM_H
