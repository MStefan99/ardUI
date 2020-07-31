//
// Created by MStefan99 on 17.12.19.
//

#ifndef ARDUI_LAYOUT_INFLATER_H
#define ARDUI_LAYOUT_INFLATER_H


#include "platform.h"
#include "view.h"


class layoutInflater {
public:
	layoutInflater() = default;

	static view& inflate(const String& xmlData, view& rootView);

private:
};

#endif //ARDUI_LAYOUT_INFLATER_H
