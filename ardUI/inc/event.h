//
// Created by MStefan99 on 17.10.20.
//

#ifndef ARDUI_EVENT_H
#define ARDUI_EVENT_H


#include "platform.h"


struct Event {
	enum Action {
		NO_ACTION,
		CLICK,
		LONG_CLICK,
		SCROLL
	};

	Action currentAction {NO_ACTION};
	uint16_t targetX {0};
	uint16_t targetY {0};
	int16_t deltaX {0};
	int16_t deltaY {0};
};

#endif //ARDUI_EVENT_H
