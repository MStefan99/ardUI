//
// Created by MStefan99 on 3.2.20.
//

#include <iostream>
#include <cstring>

#include "vector.h"
#include "list.h"
#include "map.h"
#include "stack.h"
#include "queue.h"


// Needed to avoid undefined reference error, usually defined with setup() and loop()
void arduiUserSetup() {}


void arduiUserLoop() {}


class AssertException: public std::exception {
public:
	explicit AssertException(const char* description) {
		desc = new char[strlen(description) + 1];
		strcpy(desc, description);
	}


	~AssertException() override { delete[] desc; }


	const char* what() const noexcept override { return desc; }


private:
	char* desc {nullptr};
};

using namespace std;


template <class T>
void assert(T c) {
	if (!c) {
		cerr << "True assert failed!" << endl;
		throw AssertException("True assert failed");
	}
}


template <class T>
void assertFalse(T c) {
	if (c) {
		cerr << "False assert failed!" << endl;
		throw AssertException("False assert failed");
	}
}


template <class T>
void assert(T c1, T c2) {
	if (c1 != c2) {
		cerr << "Object comparison assert failed!" << endl;
		throw AssertException("Object comparison assert failed");
	}
}


template <class T>
void assertFalse(T c1, T c2) {
	if (c1 == c2) {
		cerr << "Object false comparison assert failed!" << endl;
		throw AssertException("Object false comparison assert failed");
	}
}


void vectorAssert() {
	ardui::vector<int> v {};

	assert(v.empty(), true);
	// Push and subscript assert
	for (int i = 0; i < 10; ++i) {
		v.push_back(i);
	}
	assert(v.empty(), false);

	for (int j = 0; j < 10; ++j) {
		assert(v[j], j);
	}

	assert(*v.begin(), 0);
	assert(*--v.end(), 9);

	// erase assert
	auto it = v.erase(v.begin());
	assert(*it, 1);
	v.erase(v.begin() + 5);
	it = v.erase(v.begin() + 3, v.begin() + 4);
	assert(*it, 5);
	v.erase(v.end());

	assert(v[0], 1);
	assert(v[3], 5);
	assert(v[4], 7);
	assert(v[6], 9);
	assert(v.size(), 7);

	// insert assert
	v.insert(v.begin() + 2, -2);
	it = v.insert(v.begin() + 6, -1);
	assert(*it, -1);

	assert(v[2], -2);
	assert(v[3], 3);
	assert(v[6], -1);
	assert(v[7], 8);
	assert(v.size(), 9);

	// pop assert
	v.pop_back();
	assert(*--v.end(), 8);

	// clear assert
	v.clear();
	assert(v.size(), 0);
}


void listAssert() {
	ardui::list<int> l {};

	assert(l.empty(), true);
	// Push and subscript assert
	for (int i = 0; i < 10; ++i) {
		l.push_back(i);
	}
	assert(l.empty(), false);

	for (int j = 0; j < 10; ++j) {
		assert(l[j], j);
	}

	assert(l.size(), 10);
	assert(*l.begin(), 0);
	assert(l[5], 5);
	assert(l[8], 8);

	// insert assert
	l.insert(l.begin(), -1);
	l.insert(++l.begin(), -2);
	assert(l[0], -1);
	assert(l[1], -2);
	assert(l[2], 0);
	assert(l[3], 1);
	assert(l.size(), 12);

	// erase assert
	auto it {l.begin()};
	it = l.erase(++it);
	++it;
	it = l.erase(++it);
	it = l.erase(it, ++it);
	it = l.erase(it);
	assert(l.size(), 8);

	assert(l[0], -1);
	assert(l[1], 0);
	assert(l[2], 1);
	assert(l[3], 5);

	// remove assert
	int i = l.remove(6);
	assert(l[4], 7);
	assert(i, 1);
	i = l.remove_if([](const int& e) -> bool {
		return !e;
	});
	assert(l[1], 1);
	assert(i, 1);

	assert(l.size(), 6);
	assert(l.front(), -1);
	assert(l.back(), 9);
	assert(*--l.end(), 9);

	ardui::list<int> l2 {l};

	assert(l2.size(), 6);
	assert(l2.front(), -1);
	assert(l2.back(), 9);
	assert(*--l2.end(), 9);
}


void mapAssert() {
	ardui::map<int, double> m {};

	// insert assert
	assert(m.empty(), true);
	m.insert({2, 2.2});
	assert(m[2], 2.2);
	m.insert({-1, -1.1});
	m[-2] = -2.2;
	m[0] = 0;
	assert(m[0], 0.0);
	m[4] = 4.4;
	m[3] = 3.3;
	m[5] = 5.5;
	m[1] = 1.1;

	// size assert
	assert(m.size(), 8);
	assert(m.empty(), false);

	// erase assert
	auto it {--m.end()};
	it = m.erase(--it);
	m.erase(3);
	assert(m.size(), 6);
	it = m.erase(m.find(-1), m.find(5));
	assert(m.size(), 2);
	assert(it, m.find(5));
}


void stackAssert() {
	ardui::stack<int> s;

	s.push(1);
	s.push(2);
	s.push(3);

	// Size assert
	assert(s.size(), 3);
	assert(s.empty(), false);

	// Pop assert
	assert(s.top(), 3);
	s.pop();
	assert(s.top(), 2);
}


void queueAssert() {
	ardui::queue<int> q;

	q.push(1);
	q.push(2);
	q.push(3);

	// Size assert
	assert(q.size(), 3);
	assert(q.empty(), false);

	// Front and back assert
	assert(q.back(), 3);
	assert(q.front(), 1);

	// Pop assert
	q.pop();
	assert(q.front(), 2);
}


int main() {
	try {
		vectorAssert();
		listAssert();
		mapAssert();
		stackAssert();
		queueAssert();

		cout << "All tests passed successfully!" << endl;
	} catch (const AssertException& e) {
		cout << "The following exception occurred while running the tests: " << e.what() << std::endl;
	}
}