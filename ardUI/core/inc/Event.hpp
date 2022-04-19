//
// Created by MStefan99 on 17.10.20.
//

#ifndef ARDUI_EVENT_HPP
#define ARDUI_EVENT_HPP

#include "platform.hpp"


struct Event {
	enum Action {
		NO_ACTION,
		TOUCH,
		CLICK,
		LONG_CLICK,
		SCROLL
	};

	Action currentAction {NO_ACTION};
	int16_t targetX {0};
	int16_t targetY {0};
	int16_t deltaX {0};
	int16_t deltaY {0};
};

#endif //ARDUI_EVENT_HPP
