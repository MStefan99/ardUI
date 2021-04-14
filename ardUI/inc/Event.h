//
// Created by MStefan99 on 17.10.20.
//

#ifndef ARDUI_EVENT_H
#define ARDUI_EVENT_H

#include "platform.h"


struct Event {
	enum Action {
		NO_ACTION,
		TOUCH,
		CLICK,
		LONG_CLICK,
		SCROLL
	};

	Action _currentAction {NO_ACTION};
	uint16_t _targetX {0};
	uint16_t _targetY {0};
	int16_t _deltaX {0};
	int16_t _deltaY {0};
};

#endif //ARDUI_EVENT_H
