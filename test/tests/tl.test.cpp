//
// Created by MStefan99 on 3.2.20.
//

#include <new>

#include "Tester.hpp"

#include "platform.hpp"

#include "vector.hpp"
#include "list.hpp"
#include "map.hpp"
#include "stack.hpp"
#include "queue.hpp"


#if !USE_NEW

#include <cstdlib>

#endif


template <class T>
struct Allocator {
	using value_type = T;

	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;

	using size_type = unsigned int;
	using difference_type = unsigned long;

	#if USE_NEW


	pointer allocate(size_type n) {
		auto p = static_cast<pointer>(::operator new(sizeof(T) * n));
		_deallocated.push_back(p);
		return p;
	}


	static void clean_up() {
		while (auto p {_deallocated.front()}) {
			::operator delete(p);
			_deallocated.remove(p);
		}
	}


	#else


	pointer allocate(size_type n = 1) {
		auto p = static_cast<pointer>(std::malloc(sizeof(T) * n));
		return p;
	}


	static void clean_up() {
		while (!_deallocated.empty()) {
			std::free(_deallocated.front());
			_deallocated.pop_front();
		}
	}


	#endif


	void deallocate(pointer p, size_type n = 1) {
		_deallocated.push_back(p);
	}


	template <class U, class... Args>
	void construct(U* p, Args&& ... args) {
		::new(static_cast<void*>(p)) U(args...);
	}


	template <class U>
	void destroy(U* p) {
		p->~U();
	}


protected:
	static tl::list<T*> _deallocated;
};


template <class T>
tl::list<T*> Allocator<T>::_deallocated {};


struct AllocatorTester {
	unsigned int constructed {0};
	unsigned int destroyed {0};


	AllocatorTester() { ++constructed; }


	~AllocatorTester() { ++destroyed; }


	// Non-default constructor that will initialize members
	explicit AllocatorTester(int) {};


	AllocatorTester& operator=(const AllocatorTester& t) {
		if (this != &t) {
			if (constructed) {
				constructed = t.constructed;
				destroyed = t.destroyed;
			}
		}
		return *this;
	}
};


static void allocatorTests() {
	describe("Allocator tests", [&](TestSuite& suite) {
		suite.test("Allocating built-in types", [&] {
			tl::allocator<int> a {};
			int* i = a.allocate();
			a.construct(i, 5);

			expect(*i).toEqual(5);

			a.destroy(i);
			a.deallocate(i);
		});

		suite.test("Allocating standard types", [&] {
			tl::allocator<std::string> a;

			std::string* s = a.allocate();
			a.construct(s, "test");

			expect(*s).toEqual("test");

			a.destroy(s);
			a.deallocate(s);
		});

		suite.test("Allocating custom types", [&] {
			tl::allocator<AllocatorTester> a;

			AllocatorTester* t = a.allocate();

			a.construct(t);
			expect(t->constructed).toEqual(1);
			expect(t->destroyed).toEqual(0);
			a.destroy(t);
			expect(t->constructed).toEqual(1);
			expect(t->destroyed).toEqual(1);

			a.deallocate(t);
		});
	});
}


static void vectorTests() {
	tl::vector<int> v {};
	describe("Vector tests", [&](TestSuite& suite) {

		suite.test("Pushing elements", [&] {
			auto v1 = new tl::vector<int> {v};
			expect(v.empty()).toBeTruthy();
			expect(v.capacity()).toBeFalsy();
			for (int i = 0; i < 10; ++i) {
				v.push_back(i);
			}
			expect(v.empty()).toBeFalsy();
			expect(v.size()).toEqual(10);

			v.reserve(15);
			expect(v.capacity()).toEqual(15);

			for (int j = 0; j < 10; ++j) {
				expect(v[j]).toEqual(j);
			}

			expect(*v.begin()).toEqual(0);
			expect(*--v.end()).toEqual(9);
			delete (v1);
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
			tl::advance(it, 3);
			expect(*it).toEqual(3);

			tl::vector<tl::vector<int>> v1;
			v1.push_back(tl::vector<int> {});
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

		suite.test("Erasing elements", [&] {
			auto it = v.erase(++v.begin());
			expect(*it).toEqual(2);
			expect(v.front()).toEqual(0);
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

		suite.test("Inserting elements", [&] {
			v.insert(v.begin() + 2, -2);
			auto it = v.insert(v.begin() + 6, -1);
			expect(*it).toEqual(-1);

			expect(v[2]).toEqual(-2);
			expect(v[3]).toEqual(3);
			expect(v[6]).toEqual(-1);
			expect(v[7]).toEqual(8);
			expect(v.size()).toEqual(9);
		});

		suite.test("Editing elements", [&] {
			v[2] = 20;
			expect(v[2]).toEqual(20);
			auto it = v.begin() += 3;
			it = 30;
			expect(*it).toEqual(30);
			it[1] = 40;
			expect(*++it).toEqual(40);

			auto array = v.data();
			const auto constArray = v.data();

			for (auto i {0}; i < v.size() - 1; ++i) {
				expect(array[i]).toEqual(v[i]);
				expect(constArray[i]).toEqual(v[i]);
			}
			array[0] = 5;
			expect(*v.begin()).toEqual(5);
			expect(v.front()).toEqual(5);
			array[v.size() - 1] = -5;
			expect(*--v.end()).toEqual(-5);
			expect(v.back()).toEqual(-5);
		});

		suite.test("Copying vector", [&] {
			tl::vector<int> v1 {v};  // NOLINT(performance-unnecessary-copy-initialization)
			tl::vector<int> v2 {v};

			v2 = v1;

			expect(v1.size()).toEqual(v.size());
			expect(v2.size()).toEqual(v.size());

			expect(v1.capacity()).toEqual(v.capacity());
			expect(v2.capacity()).toEqual(v.capacity());

			for (auto i {0}; i < v.size(); ++i) {
				expect(v[i]).toEqual(v1[i]);
				expect(v[i]).toEqual(v2[i]);
			}

			v2.resize(5);
			expect(v2.size()).toEqual(5);
			expect(v2.capacity()).toEqual(v.capacity());
		});

		suite.test("Assigning vector", [&] {
			tl::vector<int> v1;
			tl::vector<int> v2;

			for (unsigned int i {0}; i < 10; ++i) {
				v1.push_back(i);
				v2.push_back(10 - i);

				expect(v1[i]).toEqual(i);
				expect(v2[i]).toEqual(10 - i);
			}

			v1 = v2;

			for (unsigned int i {0}; i < 10; ++i) {
				expect(v1[i]).toEqual(v2[i]);
			}
		});

		suite.test("Popping elements", [&] {
			v.pop_back();
			expect(*--v.end()).toEqual(8);
		});

		suite.test("Clearing vector", [&] {
			v.clear();
			expect(v.size()).toEqual(0);
		});

		// TODO: test other containers
		suite.test("Constructing and destroying elements", [&] {
			auto va = new tl::vector<AllocatorTester, Allocator<AllocatorTester>>;

			va->reserve(20);
			for (unsigned int i {0}; i < va->capacity(); ++i) {
				// Initializing values for testing
				::new(static_cast<void*>(&(*va)[i])) AllocatorTester(1);

				expect((*va)[i].constructed).toEqual(0);
				expect((*va)[i].destroyed).toEqual(0);
			}

			va->resize(10);
			for (unsigned int i {0}; i < va->size(); ++i) {
				expect((*va)[i].constructed).toEqual(1);
				expect((*va)[i].destroyed).toEqual(0);
			}
			for (unsigned int i {va->size()}; i < va->capacity(); ++i) {
				expect((*va)[i].constructed).toEqual((*va)[i].destroyed);
				expect((*va)[i].destroyed).toBeLessThan(2);
			}

			va->resize(5);
			for (unsigned int i {0}; i < va->size(); ++i) {
				expect((*va)[i].constructed).toEqual(1);
				expect((*va)[i].destroyed).toEqual(0);
			}
			for (unsigned int i {va->size()}; i < 10; ++i) {
				expect((*va)[i].constructed).toEqual(1);
				expect((*va)[i].destroyed).toEqual(1);
			}
			for (unsigned int i {10}; i < va->capacity(); ++i) {
				expect((*va)[i].constructed).toEqual((*va)[i].destroyed);
				expect((*va)[i].destroyed).toBeLessThan(2);
			}
			va->shrink_to_fit();
			expect(va->size()).toEqual(va->capacity());

			va->push_back({});
			expect(va->back().constructed).toEqual(1);
			expect(va->back().destroyed).toEqual(0);
			va->pop_back();
			expect((*va)[va->size()].constructed).toEqual(1);
			expect((*va)[va->size()].destroyed).toEqual(1);

			va->shrink_to_fit();

			va->insert(va->begin(), {});
			for (unsigned int i {0}; i < va->size(); ++i) {
				expect((*va)[i].constructed).toEqual(1);
				expect((*va)[i].destroyed).toEqual(0);
			}
			for (unsigned int i {va->size()}; i < va->capacity(); ++i) {
				// Initializing values for testing
				::new(static_cast<void*>(&(*va)[i])) AllocatorTester(1);
			}

			va->erase(va->begin());
			for (unsigned int i {0}; i < va->size(); ++i) {
				expect((*va)[i].constructed).toEqual(1);
				expect((*va)[i].destroyed).toEqual(0);
			}
			for (unsigned int i {va->size()}; i < va->capacity(); ++i) {
				expect((*va)[i].constructed).toEqual((*va)[i].destroyed);
				expect((*va)[i].destroyed).toBeLessThan(2);
			}

			va->erase(va->begin(), va->end() - 2);
			for (unsigned int i {0}; i < va->size(); ++i) {
				expect((*va)[i].constructed).toEqual(1);
				expect((*va)[i].destroyed).toEqual(0);
			}
			for (unsigned int i {va->size()}; i < va->capacity(); ++i) {
				expect((*va)[i].constructed).toEqual((*va)[i].destroyed);
				expect((*va)[i].destroyed).toBeLessThan(2);
			}

			va->clear();
			for (unsigned int i {va->size()}; i < va->capacity(); ++i) {
				expect((*va)[i].constructed).toEqual((*va)[i].destroyed);
				expect((*va)[i].destroyed).toBeLessThan(2);
			}

			delete (va);
			Allocator<AllocatorTester>::clean_up();
		});

		suite.test("Copying empty vector", [&] {
			tl::vector<int> {tl::vector<int> {}};
		});

		suite.test("Nesting vectors", [&] {
			tl::vector<int> vt {};
			tl::vector<tl::vector<int>> vv {};

			for (auto i {0}; i < 2; ++i) {
				vt.push_back(i);
				vv.push_back(vt);
			}
		});
	});
}


static void listTests() {
	tl::list<int> l {};
	describe("List tests", [&](TestSuite& suite) {

		suite.test("Pushing elements", [&] {
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

			tl::list<tl::list<int>> l1 {};
			l1.push_back({});
			expect(l1.begin()->empty()).toBeTruthy();
		});

		suite.test("Iterator arithmetics", [&] {
			auto it {l.begin()};
			expect(*it++).toEqual(0);
			expect(*++it).toEqual(2);

			it = l.begin();
			tl::advance(it, 3);
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

		suite.test("Inserting elements", [&] {
			l.insert(l.begin(), -1);
			l.insert(++l.begin(), -2);
			expect(l.size()).toEqual(12);

			tl::list<int> l1;
			l1.insert(l1.begin(), 1);
			l1.insert(l1.end(), 2);
			expect(l1.front()).toEqual(1);
			expect(l1.back()).toEqual(2);
		});

		suite.test("Erasing elements", [&] {
			auto it {l.begin()};
			it = l.erase(++it);
			++it;
			it = l.erase(++it);
			it = l.erase(it, ++it);
			it = l.erase(it);
			expect(l.size()).toEqual(8);
		});

		suite.test("Removing elements", [&] {
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

		suite.test("Editing elements", [&] {
			expect(l.front()).toEqual(-1);

			l.begin() = -2;
			expect(l.front()).toEqual(-2);
		});

		suite.test("Copying list", [&] {
			tl::list<int> l1 {l};  // NOLINT(performance-unnecessary-copy-initialization)
			tl::list<int> l2;
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

		suite.test("Copying empty list", [&] {
			tl::list<int> l1 {tl::list<int> {}};

			expect(l1.empty()).toBeTruthy();
		});
	});
}


static void mapTests() {
	tl::map<int, double> m {};
	describe("Map tests", [&](TestSuite& suite) {

		suite.test("Inserting elements", [&] {
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
			tl::advance(it, 3);
			expect(it->first).toEqual(1);

			expect(m.size()).toEqual(8);
			expect(m.empty()).toBeFalsy();
		});

		suite.test("Copying map", [&] {
			tl::map<int, double> m1 {m};
			expect(m1.size()).toEqual(8);
			expect(m1[0]).toEqual(0.0);
		});

		suite.test("Erasing elements", [&] {
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
			tl::map<int, int> mLeft {};
			mLeft[3] = 3;
			mLeft[2] = 2;
			mLeft[1] = 1;

			tl::map<int, int> mRight {};
			mRight[1] = 1;
			mRight[2] = 2;
			mRight[3] = 3;

			// TODO: what exactly is this testing? remake!
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
			--it;
		});

		suite.test("Special copy cases", [&] {
			tl::map<int, double> m1 {tl::map<int, double> {}};
			expect(m1.empty()).toBeTruthy();

			tl::map<int, double> m2 {};
			m2[0] = 0;
			auto m3 {m2};
			expect(m3.size()).toEqual(1);
		});
	});
}


static void stackTests() {
	tl::stack<int> s;
	describe("Stack tests", [&](TestSuite& suite) {

		suite.test("Pushing elements", [&] {
			s.push(1);
			s.push(2);
			s.push(3);

			expect(s.size()).toEqual(3);
			expect(s.empty()).toBeFalsy();
		});

		suite.test("Popping elements", [&] {
			expect(s.top()).toEqual(3);
			s.pop();
			expect(s.top()).toEqual(2);
		});
	});
}


static void queueTests() {
	tl::queue<int> q;
	describe("Queue tests", [&](TestSuite& suite) {

		suite.test("Pushing elements", [&] {
			q.push(1);
			q.push(2);
			q.push(3);

			expect(q.back()).toEqual(3);
			expect(q.front()).toEqual(1);

			expect(q.size()).toEqual(3);
			expect(q.empty()).toBeFalsy();
		});

		suite.test("Popping elements", [&] {
			q.pop();
			expect(q.front()).toEqual(2);
		});
	});
}


int main() {
	allocatorTests();
	vectorTests();
	listTests();
	mapTests();
	stackTests();
	queueTests();

	return 0;
}