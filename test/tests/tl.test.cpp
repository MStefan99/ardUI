//
// Created by MStefan99 on 3.2.20.
//

#include "Tester.h"
#include "vector.h"
#include "list.h"
#include "map.h"
#include "stack.h"
#include "queue.h"


void vectorAssert() {
	ardui::vector<int> v {};
	describe("Vector check", [&](TestSuite& suite) -> void {

		suite.test("push and subscribe", [&]() -> void {
			expect(v.empty()).toBeTruthy();
			expect(v.capacity()).toBeFalsy();
			for (int i = 0; i < 10; ++i) {
				v.push_back(i);
			}
			expect(v.empty()).toBeFalsy();
			expect(v.size()).toEqual(10);

			for (int j = 0; j < 10; ++j) {
				expect(v[j]).toEqual(j);
			}

			expect(*v.begin()).toEqual(0);
			expect(*--v.end()).toEqual(9);
		});

		suite.test("Iterator arithmetics", [&]() -> void {
			auto it = v.begin();
			expect(*++it).toEqual(1);
			expect(*--it).toEqual(0);
			expect(*(it += 3)).toEqual(3);
			expect(*(it -= 2)).toEqual(1);
			it++;
			expect(*it).toEqual(2);
			it--;
			expect(*it).toEqual(1);

			ardui::vector<ardui::vector<int>> v1;
			v1.push_back(ardui::vector<int> {});
			expect(v1.begin()->size()).toBeFalsy();
		});

		suite.test("Iterator comparison", [&]() -> void {
			expect(v.begin()).toEqual(v.begin());
			expect(v.begin()).toDiffer(++v.begin());
			expect(v.begin()).toBeLessThan(++v.begin());
			expect(++v.begin()).toBeGreaterThan(v.begin());
			expect(v.begin()).toBeLessThanOrEqual(++v.begin());
			expect(++v.begin()).toBeGreaterThanOrEqual(v.begin());
		});

		suite.test("erase", [&]() -> void {
			auto it = v.erase(++v.begin());
			expect(*it).toEqual(2);
			v.erase(v.begin() + 5);
			it = v.erase(v.begin() + 3, v.begin() + 4);
			expect(*it).toEqual(5);
			v.erase(v.end());

			expect(v[1]).toEqual(2);
			expect(v[3]).toEqual(5);
			expect(v[4]).toEqual(7);
			expect(v[6]).toEqual(9);
			expect(v.size()).toEqual(7);
		});

		suite.test("insert", [&]() -> void {
			v.insert(v.begin() + 2, -2);
			auto it = v.insert(v.begin() + 6, -1);
			expect(*it).toEqual(-1);

			expect(v[2]).toEqual(-2);
			expect(v[3]).toEqual(3);
			expect(v[6]).toEqual(-1);
			expect(v[7]).toEqual(8);
			expect(v.size()).toEqual(9);
		});

		suite.test("Edit elements", [&]() -> void {
			v[2] = 20;
			expect(v[2]).toEqual(20);
			auto it = v.begin() += 3;
			it = 30;
			expect(*it).toEqual(30);
			it[1] = 40;
			expect(*++it).toEqual(40);
		});

		suite.test("copy", [&]() -> void {
			ardui::vector<int> v1 {v};  // NOLINT(performance-unnecessary-copy-initialization)
			ardui::vector<int> v2;

			v2 = v1;
			expect(v1.size()).toEqual(9);
			expect(v2.size()).toEqual(9);

			for (auto i {0}; i < v.size(); ++i) {
				expect(v[i]).toEqual(v1[i]);
				expect(v[i]).toEqual(v2[i]);
			}
		});

		suite.test("pop", [&]() -> void {
			v.pop_back();
			expect(*--v.end()).toEqual(8);
		});

		suite.test("clear", [&]() -> void {
			v.clear();
			expect(v.size()).toEqual(0);
		});

		suite.test("empty copy", [&]() -> void {
			ardui::vector<int> {ardui::vector<int> {}};
		});

		suite.test("Insert resize", [&]() -> void {
			for (int i = 0; i < 20; ++i) {
				v.insert(v.begin(), i);
			}

			for (int j = 0; j < 20; ++j) {
				expect(v[j]).toEqual(19 - j);
			}
		});
	});
}


void listAssert() {
	ardui::list<int> l {};
	describe("List check", [&](TestSuite& suite) -> void {

		expect(l.empty()).toBeTruthy();
		suite.test("push and subscript assert", [&]() -> void {
			for (int i = 0; i < 10; ++i) {
				l.push_back(i);
			}
			expect(l.empty()).toBeFalsy();

			for (int j = 0; j < 10; ++j) {
				expect(l[j]).toEqual(j);
			}

			expect(l.size()).toEqual(10);
			expect(*l.begin()).toEqual(0);
			expect(l[5]).toEqual(5);
			expect(l[8]).toEqual(8);
		});

		suite.test("insert assert", [&]() -> void {
			l.insert(l.begin(), -1);
			l.insert(++l.begin(), -2);
			expect(l[0]).toEqual(-1);
			expect(l[1]).toEqual(-2);
			expect(l[2]).toEqual(0);
			expect(l[3]).toEqual(1);
			expect(l.size()).toEqual(12);
		});

		suite.test("erase assert", [&]() -> void {
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
		});

		suite.test("remove assert", [&]() -> void {
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
		});

		suite.test("copy assert", [&]() -> void {
			ardui::list<int> l1 {l};
			expect(l1.size()).toEqual(6);
			expect(l1.front()).toEqual(-1);
			expect(l1.back()).toEqual(9);
			expect(*--l1.end()).toEqual(9);
		});

		suite.test("empty copy assert", [&]() -> void {
			ardui::list<int> {ardui::list<int> {}};
		});
	});
}


void mapAssert() {
	ardui::map<int, double> m {};
	describe("Map check", [&](TestSuite& suite) -> void {

		suite.test("insert assert", [&]() -> void {
			expect(m.empty()).toBeTruthy();
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
		});

		suite.test("size assert", [&]() -> void {
			expect(m.size()).toEqual(8);
			expect(m.empty()).toBeFalsy();
		});

		suite.test("copy assert", [&]() -> void {
			ardui::map<int, double> m1 {m};
			expect(m1.size()).toEqual(8);
			expect(m1[0]).toEqual(0.0);
		});

		suite.test("erase assert", [&]() -> void {
			auto it {--m.end()};
			it = m.erase(--it);
			m.erase(3);
			expect(m.size()).toEqual(6);
			it = m.erase(m.find(-1), m.find(5));
			expect(m.size()).toEqual(2);
			expect(it).toEqual(m.find(5));
		});

		suite.test("Unbalanced iteration assert", [&]() -> void {
			ardui::map<int, int> m2 {};
			m2[2] = 2;
			m2[1] = 1;

			for (const auto& i : m2) {}
		});

		suite.test("empty copy assert", [&]() -> void {
			ardui::map<int, double> {ardui::map<int, double> {}};
		});

		//
	});
}


void stackAssert() {
	ardui::stack<int> s;
	describe("Stack check", [&](TestSuite& suite) -> void {

		suite.beforeAll([&]() -> void {
			s.push(1);
			s.push(2);
			s.push(3);
		});

		suite.test("Size assert", [&]() -> void {
			expect(s.size()).toEqual(3);
			expect(s.empty()).toBeFalsy();
		});

		suite.test("Pop assert", [&]() -> void {
			expect(s.top()).toEqual(3);
			s.pop();
			expect(s.top()).toEqual(2);
		});
	});
}


void queueAssert() {
	ardui::queue<int> q;
	describe("Queue check", [&](TestSuite& suite) -> void {

		suite.beforeAll([&]() -> void {
			q.push(1);
			q.push(2);
			q.push(3);
		});

		suite.test("Size assert", [&]() -> void {
			expect(q.size()).toEqual(3);
			expect(q.empty()).toBeFalsy();
		});

		suite.test("Front and back assert", [&]() -> void {
			expect(q.back()).toEqual(3);
			expect(q.front()).toEqual(1);
		});

		suite.test("Pop assert", [&]() -> void {
			q.pop();
			expect(q.front()).toEqual(2);
		});
	});
}


int main() {
	vectorAssert();
	listAssert();
	mapAssert();
	stackAssert();
	queueAssert();
}