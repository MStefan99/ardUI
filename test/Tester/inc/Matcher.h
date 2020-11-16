//
// Created by MStefan99 on 16.11.20.
//

#ifndef ARDUI_MATCHER_H
#define ARDUI_MATCHER_H


#include "AssertException.h"


class Matcher {
public:
	Matcher() = default;

	explicit Matcher(void* expression):
			expression {expression} {}

	template <class T>
	void toEqual(T expected) {
		T actual = *(T*)expression;
		if (actual != expected) {
			throw AssertException("Test failed. Expected: "
														+ std::to_string(expected) + ", got: "
														+ std::to_string(actual) + ".");
		}
	}

private:
	void* expression {nullptr};
};


template <class T>
Matcher expect(T actual) {
	return Matcher {&actual};
}

#endif //ARDUI_MATCHER_H
