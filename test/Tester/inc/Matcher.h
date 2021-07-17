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
	void toDiffer(T expected) const;
	void toBeGreaterThan(T expected) const;
	void toBeGreaterThanOrEqual(T expected) const;
	void toBeLessThan(T expected) const;
	void toBeLessThanOrEqual(T expected) const;
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
				"Actual value does not match the expected value" :
				"Actual value should not match the expected value");
	}
}


template <class T>
void Matcher<T>::toDiffer(T expected) const {
	if ((_actual != expected) ^ _negated) {
		return;
	} else {
		throw AssertException(!_negated?
				"Actual value does not differ from the expected value" :
				"Actual value should not differ from the expected value");
	}
}


template <class T>
void Matcher<T>::toBeGreaterThan(T expected) const {
	if ((_actual > expected) ^ _negated) {
		return;
	} else {
		throw AssertException(!_negated?
				"Actual value is not greater than the expected value" :
				"Actual value should not be greater than the expected value");
	}
}


template <class T>
void Matcher<T>::toBeGreaterThanOrEqual(T expected) const {
	if ((_actual >= expected) ^ _negated) {
		return;
	} else {
		throw AssertException(!_negated?
				"Actual value is not greater than or equal to the expected value" :
				"Actual value should not be greater than or equal to the expected value");
	}
}


template <class T>
void Matcher<T>::toBeLessThan(T expected) const {
	if ((_actual < expected) ^ _negated) {
		return;
	} else {
		throw AssertException(!_negated?
				"Actual value is not less than the expected value" :
				"Actual value should not be less than the expected value");
	}
}


template <class T>
void Matcher<T>::toBeLessThanOrEqual(T expected) const {
	if ((_actual <= expected) ^ _negated) {
		return;
	} else {
		throw AssertException(!_negated?
				"Actual value is not less than or equal to the expected value" :
				"Actual value should not be less than or equal to the expected value");
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
	if (!!_actual ^ _negated) {
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
