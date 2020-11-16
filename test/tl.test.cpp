//
// Created by MStefan99 on 3.2.20.
//

#include <iostream>
#include <cstring>

#include "Tester/inc/TestBlock.h"
#include "vector.h"
#include "list.h"
#include "map.h"
#include "stack.h"
#include "queue.h"


// Needed to avoid undefined reference error, usually defined with setup() and loop()
void arduiUserSetup() {}


void arduiUserLoop() {}


void vectorAssert() {
	ardui::vector<int> v {};

	expect(v.empty()).toEqual(true);
	// Push and subscript assert
	for (int i = 0; i < 10; ++i) {
		v.push_back(i);
	}
	expect(v.empty()).toEqual(false);

	for (int j = 0; j < 10; ++j) {
		expect(v[j]).toEqual(j);
	}

	expect(*v.begin()).toEqual(0);
	expect(*--v.end()).toEqual(9);

	// erase assert
	auto it = v.erase(v.begin());
	expect(*it).toEqual(1);
	v.erase(v.begin() + 5);
	it = v.erase(v.begin() + 3, v.begin() + 4);
	expect(*it).toEqual(5);
	v.erase(v.end());

	expect(v[0]).toEqual(1);
	expect(v[3]).toEqual(5);
	expect(v[4]).toEqual(7);
	expect(v[6]).toEqual(9);
	expect(v.size()).toEqual(7);

	// insert assert
	v.insert(v.begin() + 2, -2);
	it = v.insert(v.begin() + 6, -1);
	expect(*it).toEqual(-1);

	expect(v[2]).toEqual(-2);
	expect(v[3]).toEqual(3);
	expect(v[6]).toEqual(-1);
	expect(v[7]).toEqual(8);
	expect(v.size()).toEqual(9);

	// copy assert
	ardui::vector<int> v1 {v};
	expect(v1.size()).toEqual(9);

	// pop assert
	v.pop_back();
	expect(*--v.end()).toEqual(8);

	// clear assert
	v.clear();
	expect(v.size()).toEqual(0);

	// empty copy assert
	ardui::vector<int> {ardui::vector<int> {}};
}


void listAssert() {
	ardui::list<int> l {};

	expect(l.empty()).toEqual(true);
	// Push and subscript assert
	for (int i = 0; i < 10; ++i) {
		l.push_back(i);
	}
	expect(l.empty()).toEqual(false);

	for (int j = 0; j < 10; ++j) {
		expect(l[j]).toEqual(j);
	}

	expect(l.size()).toEqual(10);
	expect(*l.begin()).toEqual(0);
	expect(l[5]).toEqual(5);
	expect(l[8]).toEqual(8);

	// insert assert
	l.insert(l.begin(), -1);
	l.insert(++l.begin(), -2);
	expect(l[0]).toEqual(-1);
	expect(l[1]).toEqual(-2);
	expect(l[2]).toEqual(0);
	expect(l[3]).toEqual(1);
	expect(l.size()).toEqual(12);

	// erase assert
	auto it {l.begin()};
	it = l.erase(++it);
	++it;
	it = l.erase(++it);
	it = l.erase(it, ++it);
	it = l.erase(it);
	expect(l.size()).toEqual(8);
	expect(l[0]).toEqual(-1);
	expect(l[1]).toEqual(0);
	expect(l[2]).toEqual(1);
	expect(l[3]).toEqual(5);

	// remove assert
	int i = l.remove(6);
	expect(l[4]).toEqual(7);
	expect(i).toEqual(1);
	i = l.remove_if([](const int& e) -> bool {
		return !e;
	});
	expect(l[1]).toEqual(1);
	expect(i).toEqual(1);
	expect(l.size()).toEqual(6);
	expect(l.front()).toEqual(-1);
	expect(l.back()).toEqual(9);
	expect(*--l.end()).toEqual(9);

	// copy assert
	ardui::list<int> l1 {l};
	expect(l1.size()).toEqual(6);
	expect(l1.front()).toEqual(-1);
	expect(l1.back()).toEqual(9);
	expect(*--l1.end()).toEqual(9);

	// empty copy assert
	ardui::list<int> {ardui::list<int> {}};
}


void mapAssert() {
	ardui::map<int, double> m {};

	// insert assert
	expect(m.empty()).toEqual(true);
	m.insert({2, 2.2});
	expect(m[2]).toEqual(2.2);
	m.insert({-1, -1.1});
	m[-2] = -2.2;
	m[0] = 0;
	expect(m[0]).toEqual(0.0);
	m[4] = 4.4;
	m[3] = 3.3;
	m[5] = 5.5;
	m[1] = 1.1;

	// size assert
	expect(m.size()).toEqual(8);
	expect(m.empty()).toEqual(false);

	// copy assert
	ardui::map<int, double> m1 {m};
	expect(m1.size()).toEqual(8);
	expect(m1[0]).toEqual(0.0);

	// erase assert
	auto it {--m.end()};
	it = m.erase(--it);
	m.erase(3);
	expect(m.size()).toEqual(6);
	it = m.erase(m.find(-1), m.find(5));
	expect(m.size()).toEqual(2);
//	expect(it).toEqual(m.find(5));

	// empty copy assert
	ardui::map<int, double> {ardui::map<int, double> {}};
}


void stackAssert() {
	ardui::stack<int> s;

	s.push(1);
	s.push(2);
	s.push(3);

	// Size assert
	expect(s.size()).toEqual(3);
	expect(s.empty()).toEqual(false);

	// Pop assert
	expect(s.top()).toEqual(3);
	s.pop();
	expect(s.top()).toEqual(2);
}


void queueAssert() {
	ardui::queue<int> q;

	q.push(1);
	q.push(2);
	q.push(3);

	// Size assert
	expect(q.size()).toEqual(3);
	expect(q.empty()).toEqual(false);

	// Front and back assert
	expect(q.back()).toEqual(3);
	expect(q.front()).toEqual(1);

	// Pop assert
	q.pop();
	expect(q.front()).toEqual(2);
}


int main() {
	describe("TL check", {
		test("Vector check", {
			vectorAssert();
		});

		test("List check", {
				listAssert();
		});

		test("Map check", {
				mapAssert();
		});

		test("Stack check", {
				stackAssert();
		});

		test("Queue check", {
			queueAssert();
		});
	});
}