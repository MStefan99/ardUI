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
			_actual(expected) {
	}


	Matcher Not() {
		_negated = !_negated;
		return *this;
	}


	void toEqual(T expected) {
		if ((_actual == expected) ^ _negated) {
			return;
		} else {
			throw AssertException("toEqual error");
		}
	}


protected:
	T _actual;
	bool _negated = false;
};


template <class T>
Matcher<T> expect(T actual) {
	return Matcher<T> {actual};
}


#endif //ARDUI_MATCHER_H
