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
	explicit Matcher(T expected);

	Matcher& Not();

	void toEqual(T expected) const;
	void toBeTruthy() const;
	void toBeFalsy() const;
	void toBeNull() const;

protected:
	T _actual;
	bool _negated = false;
};


template <class T>
Matcher<T> expect(T actual) {
	return Matcher<T> {actual};
}


template <class T>
Matcher<T>::Matcher(T expected):
		_actual(expected) {
}


template <class T>
Matcher<T>& Matcher<T>::Not() {
	_negated = !_negated;
	return *this;
}


template <class T>
void Matcher<T>::toEqual(T expected) const {
	if ((_actual == expected) ^ _negated) {
		return;
	} else {
		throw AssertException(!_negated?
		                      "Actual value doesn't match the expected value" :
		                      "Actual value shouldn't match the expected value");
	}
}


template <class T>
void Matcher<T>::toBeNull() const {
	if ((_actual == nullptr) ^ _negated) {
		return;
	} else {
		throw AssertException(!_negated?
		                      "Value was expected to be null" :
		                      "Value was not expected to be null");
	}
}


template <class T>
void Matcher<T>::toBeTruthy() const {
	if (_actual ^ _negated) {
		return;
	} else {
		throw AssertException(!_negated?
		                      "Value was expected to be truthy" :
		                      "Value was not expected to be truthy");
	}
}


template <class T>
void Matcher<T>::toBeFalsy() const {
	if (!_actual ^ _negated) {
		return;
	} else {
		throw AssertException(!_negated?
		                      "Value was expected to be falsy" :
		                      "Value was not expected to be falsy");
	}
}


#endif //ARDUI_MATCHER_H
