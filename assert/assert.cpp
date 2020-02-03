//
// Created by MStefan99 on 3.2.20.
//

#include <iostream>
#include <cstring>

#include "vector.h"
#include "map.h"
#include "list.h"

class assertException : public std::exception {
public:
    explicit assertException(const char* description) {
        desc = new char[strlen(description) + 1];
        strcpy(desc, description);
    }

    ~assertException() override { delete[] desc; }

    const char * what() const noexcept override { return desc; }

private:
    char* desc {nullptr};
};


using namespace std;

template<class T>
void assert(T c) {
    if (!c) {
        cerr << "True assert failed!" << endl;
        throw assertException("True assert failed");
    }
}


template<class T>
void assertFalse(T c) {
    if (c) {
        cerr << "False assert failed!" << endl;
        throw assertException("False assert failed");
    }
}


template<class T>
void assert(T c1, T c2) {
    if (c1 != c2) {
        cerr << "Object comparison assert failed!" << endl;
        throw assertException("Object comparison assert failed");
    }
}


template<class T>
void assertFalse(T c1, T c2) {
    if (c1 == c2) {
        cerr << "Object false comparison assert failed!" << endl;
        throw assertException("Object false comparison assert failed");
    }
}


void vectorAssert() {
    ardui::vector<int> v {};

    // Push and subscript assert
    for (int i = 0; i < 10; ++i) {
        v.push_back(i);
    }

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

    // Push and subscript assert
    for (int i = 0; i < 10; ++i) {
        l.push_back(i);
    }

    for (int j = 0; j < 10; ++j) {
        assert(l[j], j);
    }

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


    // erase assert
    auto it {l.begin()};
    it = l.erase(++it);
    ++it;
    it = l.erase(++it);
    it = l.erase(it, ++it);
    it = l.erase(it);

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
}


void mapAssert() {
}


int main() {
    vectorAssert();
    listAssert();
    mapAssert();
    cout << "Tests passed successfully!" << endl;
}