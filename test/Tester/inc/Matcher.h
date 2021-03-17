//
// Created by MStefan99 on 16.11.20.
//

#ifndef ARDUI_MATCHER_H
#define ARDUI_MATCHER_H


#include <cstring>

#include "AssertException.h"


class Matcher {
public:
	Matcher() = default;


	explicit Matcher(void* exp, size_t size) {
		expression = malloc(size);
		memcpy(expression, exp, size);
	}


	~Matcher() {
		free(expression);
	}


	template <class T>
	void toEqual(T expected) {
		T actual = *(T*)expression;
		if (actual != expected) {
			throw AssertException("Expected: " + std::to_string((T)expected) + ", got: " + std::to_string((T)actual));
		}
	}


private:
	void* expression {nullptr};
};


template <class T>
Matcher expect(T actual) {
	return Matcher {&actual, sizeof(T)};
}


#endif //ARDUI_MATCHER_H
