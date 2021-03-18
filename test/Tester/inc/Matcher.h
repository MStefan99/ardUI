//
// Created by MStefan99 on 16.11.20.
//

#ifndef ARDUI_MATCHER_H
#define ARDUI_MATCHER_H


#include <cstring>

#include "AssertException.h"


template <class T>
class Matcher {
public:
	explicit Matcher(T expected):
		actual(expected) {
	}


	Matcher Not() {
		negated = !negated;
		return *this;
	}


	void toEqual(T expected) {
		if ((actual == expected) ^ negated) {
			return;
		} else {
			throw AssertException("");
		}
	}


protected:
	T actual;
	bool negated = false;
};


template <class T>
Matcher<T> expect(T actual) {
	return Matcher<T> {actual};
}


#endif //ARDUI_MATCHER_H
