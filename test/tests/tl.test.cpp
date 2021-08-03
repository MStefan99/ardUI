//
// Created by MStefan99 on 3.2.20.
//

#include "Tester.h"
#include "vector.h"
#include "list.h"
#include "map.h"
#include "stack.h"
#include "queue.h"


static void VectorAssert() {
	ardui::vector<int> v {};
	describe("Vector check", [&](TestSuite& suite) {

		suite.test("push and subscribe", [&] {
			auto v1 = new ardui::vector<int> {v};
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

		suite.test("Iterator arithmetics", [&] {
			auto it {v.begin()};
			expect(*++it).toEqual(1);
			expect(*--it).toEqual(0);
			expect(*(it += 3)).toEqual(3);
			expect(*(it -= 2)).toEqual(1);
			it++;
			expect(*it).toEqual(2);
			it--;
			expect(*it).toEqual(1);

			it = v.begin();
			ardui::advance(it, 3);
			expect(*it).toEqual(3);

			ardui::vector<ardui::vector<int>> v1;
			v1.push_back(ardui::vector<int> {});
			expect(v1.begin()->size()).toBeFalsy();
		});

		suite.test("Iterator comparison", [&] {
			expect(v.begin()).toEqual(v.begin());
			expect(v.begin()).toDiffer(++v.begin());
			expect(v.begin()).toBeLessThan(++v.begin());
			expect(++v.begin()).toBeGreaterThan(v.begin());
			expect(v.begin()).toBeLessThanOrEqual(++v.begin());
			expect(++v.begin()).toBeGreaterThanOrEqual(v.begin());
		});

		suite.test("erase", [&] {
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

		suite.test("insert", [&] {
			v.insert(v.begin() + 2, -2);
			auto it = v.insert(v.begin() + 6, -1);
			expect(*it).toEqual(-1);

			expect(v[2]).toEqual(-2);
			expect(v[3]).toEqual(3);
			expect(v[6]).toEqual(-1);
			expect(v[7]).toEqual(8);
			expect(v.size()).toEqual(9);
		});

		suite.test("Edit elements", [&] {
			v[2] = 20;
			expect(v[2]).toEqual(20);
			auto it = v.begin() += 3;
			it = 30;
			expect(*it).toEqual(30);
			it[1] = 40;
			expect(*++it).toEqual(40);
		});

		suite.test("copy", [&] {
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

		suite.test("pop", [&] {
			v.pop_back();
			expect(*--v.end()).toEqual(8);
		});

		suite.test("clear", [&] {
			v.clear();
			expect(v.size()).toEqual(0);
		});

		suite.test("empty copy", [&] {
			ardui::vector<int> {ardui::vector<int> {}};
		});

		suite.test("Insert resize", [&] {
			for (int i = 0; i < 20; ++i) {
				v.insert(v.begin(), i);
			}

			for (int j = 0; j < 20; ++j) {
				expect(v[j]).toEqual(19 - j);
			}
		});
	});
}


static void ListAssert() {
	ardui::list<int> l {};
	describe("List check", [&](TestSuite& suite) {

		suite.test("push and subscript assert", [&] {
			expect(l.empty()).toBeTruthy();
			l.push_back(1);
			expect(l.front()).toEqual(1);
			expect(l.back()).toEqual(1);
			l.pop_back();

			l.push_front(2);
			expect(l.front()).toEqual(2);
			expect(l.back()).toEqual(2);
			l.pop_front();

			expect(l.empty()).toBeTruthy();
			for (int i = 0; i < 10; ++i) {
				l.push_back(i);
			}
			expect(l.empty()).toBeFalsy();

			expect(l.size()).toEqual(10);
			expect(*l.begin()).toEqual(0);

			l.clear();
			expect(l.empty()).toBeTruthy();

			for (int i = 9; i >= 0; --i) {
				l.push_front(i);
			}
			expect(l.empty()).toBeFalsy();

			expect(l.size()).toEqual(10);
			expect(*l.begin()).toEqual(0);

			ardui::list<ardui::list<int>> l1 {};
			l1.push_back({});
			expect(l1.begin()->empty()).toBeTruthy();
		});

		suite.test("Iterator arithmetics", [&] {
			auto it {l.begin()};
			expect(*it++).toEqual(0);
			expect(*++it).toEqual(2);

			it = l.begin();
			ardui::advance(it, 3);
			expect(*it).toEqual(3);

			it = --l.end();
			expect(*it--).toEqual(9);
			expect(*--it).toEqual(7);

			it = l.end();
			it--;
			expect(*it).toEqual(9);
			++it;
			expect(*--it).toEqual(9);
			it++;
			expect(*--it).toEqual(9);
		});

		suite.test("Iterator comparison", [&] {
			expect(l.begin()).toEqual(l.begin());
			expect(l.end()).toEqual(l.end());

			expect(l.begin()).toDiffer(l.end());
		});

		suite.test("insert assert", [&] {
			l.insert(l.begin(), -1);
			l.insert(++l.begin(), -2);
			expect(l.size()).toEqual(12);

			ardui::list<int> l1;
			l1.insert(l1.begin(), 1);
			l1.insert(l1.end(), 2);
			expect(l1.front()).toEqual(1);
			expect(l1.back()).toEqual(2);
		});

		suite.test("erase assert", [&] {
			auto it {l.begin()};
			it = l.erase(++it);
			++it;
			it = l.erase(++it);
			it = l.erase(it, ++it);
			it = l.erase(it);
			expect(l.size()).toEqual(8);
		});

		suite.test("remove assert", [&] {
			int i = l.remove(6);
			expect(i).toEqual(1);
			i = l.remove_if([](const int& e) -> bool {
				return !e;
			});

			expect(i).toEqual(1);
			expect(l.size()).toEqual(6);
			expect(l.front()).toEqual(-1);
			expect(l.back()).toEqual(9);
			expect(*--l.end()).toEqual(9);
		});

		suite.test("Iterator edit", [&] {
			expect(l.front()).toEqual(-1);

			l.begin() = -2;
			expect(l.front()).toEqual(-2);
		});

		suite.test("copy assert", [&] {
			ardui::list<int> l1 {l};  // NOLINT(performance-unnecessary-copy-initialization)
			ardui::list<int> l2;
			l2 = l;

			expect(l1.size()).toEqual(6);
			expect(l1.front()).toEqual(-2);
			expect(l1.back()).toEqual(9);
			expect(*--l1.end()).toEqual(9);

			expect(l2.size()).toEqual(6);
			expect(l2.front()).toEqual(-2);
			expect(l2.back()).toEqual(9);
			expect(*--l2.end()).toEqual(9);
		});

		suite.test("empty copy assert", [&] {
			ardui::list<int> l1 {ardui::list<int> {}};

			expect(l1.empty()).toBeTruthy();
		});
	});
}


static void MapAssert() {
	ardui::map<int, double> m {};
	describe("Map check", [&](TestSuite& suite) {

		suite.test("insert assert", [&] {
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

			auto it = m.find(2);
			expect(m.insert({2, 2.2}).first).toEqual(it);
			expect(m[2]).toEqual(2.2);

			it = m.begin();
			ardui::advance(it, 3);
			expect(it->first).toEqual(1);
		});

		suite.test("size assert", [&] {
			expect(m.size()).toEqual(8);
			expect(m.empty()).toBeFalsy();
		});

		suite.test("copy assert", [&] {
			ardui::map<int, double> m1 {m};
			expect(m1.size()).toEqual(8);
			expect(m1[0]).toEqual(0.0);
		});

		suite.test("erase assert", [&] {
			auto it {--m.end()};
			it = m.erase(--it);
			m.erase(3);
			expect(m.size()).toEqual(6);
			expect(m.erase(20)).toBeFalsy();
			expect(m.size()).toEqual(6);
			it = m.erase(m.find(-1), m.find(5));
			expect(m.size()).toEqual(2);
			expect(it).toEqual(m.find(5));
		});

		suite.test("Iterator arithmetics", [&] {
			expect(m.begin()->first).toEqual(-2);
			expect((++m.begin())->first).toEqual(5);

			auto it {m.begin()};
			expect(it->first).toEqual(-2);
			it++;
			expect(it->first).toEqual(5);
			it++;
			expect((--it)->first).toEqual(5);

			it = --m.end();
			expect(it->first).toEqual(5);
			it--;
			expect(it->first).toEqual(-2);
		});

		suite.test("Unbalanced traversal", [&] {
			ardui::map<int, int> mLeft {};
			mLeft[3] = 3;
			mLeft[2] = 2;
			mLeft[1] = 1;

			ardui::map<int, int> mRight {};
			mRight[1] = 1;
			mRight[2] = 2;
			mRight[3] = 3;

			for (const auto& e : mLeft) {
				expect(e.first).toEqual(e.second);
			}
			for (const auto& e : mRight) {
				expect(e.first).toEqual(e.second);
			}
			auto it {mLeft.end()};
			for (it = --mLeft.end(); it != mLeft.begin(); --it) {
				expect(it->first).toEqual(it->second);
			}
			--it;
			for (it = --mRight.end(); it != mRight.begin(); --it) {
				expect(it->first).toEqual(it->second);
			}
			--it;  // Covers lines needed for reverse iterator
			// TODO: add reverse iterators
		});

		suite.test("Special copy cases", [&] {
			ardui::map<int, double> m1 {ardui::map<int, double> {}};
			expect(m1.empty()).toBeTruthy();

			ardui::map<int, double> m2 {};
			m2[0] = 0;
			auto m3 {m2};
			expect(m3.size()).toEqual(1);
		});
	});
}


static void StackAssert() {
	ardui::stack<int> s;
	describe("Stack check", [&](TestSuite& suite) {

		suite.beforeAll([&] {
			s.push(1);
			s.push(2);
			s.push(3);
		});

		suite.test("Size assert", [&] {
			expect(s.size()).toEqual(3);
			expect(s.empty()).toBeFalsy();
		});

		suite.test("Pop assert", [&] {
			expect(s.top()).toEqual(3);
			s.pop();
			expect(s.top()).toEqual(2);
		});
	});
}


static void QueueAssert() {
	ardui::queue<int> q;
	describe("Queue check", [&](TestSuite& suite) {

		suite.beforeAll([&] {
			q.push(1);
			q.push(2);
			q.push(3);
		});

		suite.test("Size assert", [&] {
			expect(q.size()).toEqual(3);
			expect(q.empty()).toBeFalsy();
		});

		suite.test("Front and back assert", [&] {
			expect(q.back()).toEqual(3);
			expect(q.front()).toEqual(1);
		});

		suite.test("Pop assert", [&] {
			q.pop();
			expect(q.front()).toEqual(2);
		});
	});
}


int main() {
	VectorAssert();
	ListAssert();
	MapAssert();
	StackAssert();
	QueueAssert();

	return 0;
}