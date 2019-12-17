//
// Created by MStefan99 on 25.11.19.
//

#ifndef ARDUI_SLIST_H
#define ARDUI_SLIST_H

#include "element.h"
#include "iterator.h"

template<class T>
class list {
public:
    list() = default;
    list(const list& list);
    ~list() noexcept;

    void append(const T &content);
    void prepend(const T &content);

    T pop();
    T popLeft();

    T drop(iterator<T> iterator);
    void dropIf(bool (*predicate)(const T&));

    void wipe();

    T &operator[](int n);
    list& operator=(const list& list);

    iterator<T> begin() const;
    iterator<T> end() const;
private:
    element<T>* first {nullptr};
    element<T>* last {nullptr};
};


template<class T>
list<T>::list(const list& l) {
    for (auto e : l) {
        append(e);
    }
}


template<class T>
list<T>::~list() noexcept {
    wipe();
}


template<class T>
void list<T>::append(const T &content) {
    auto e = new element<T>(content, last);

    if (!first) {
        first = e;
    }
    if (last) {
        last->setNext(e);
    }
    last = e;
}


template<class T>
void list<T>::prepend(const T &content) {
    auto e = new element<T>(content, nullptr, first);

    if (!last) {
        last = e;
    }
    if (first) {
        first->setPrev(e);
    }
    first = e;
}


template<class T>
T list<T>::pop() {
    auto e = last;
    if (e) {
        auto content = last->getContent();

        if (e->getPrev()) {
            e->getPrev()->setNext(nullptr);
        } else {
            first = nullptr;
        }

        last = e->getPrev();
        delete e;
        return content;
    } else {
        throw listException("list empty", "", __FUNCTION__, __FILE__, __LINE__);
    }
}


template<class T>
T list<T>::popLeft() {
    auto e = first;
    if (e) {
        auto content = e->getContent();

        if (e->getNext()) {
            e->getNext()->setPrev(nullptr);
        } else {
            last = nullptr;
        }
        first = e->getNext();

        delete e;
        return content;
    } else {
        throw listException("list empty", "", __FUNCTION__, __FILE__, __LINE__);
    }
}


template<class T>
T list<T>::drop(iterator<T> iterator) {
    element<T> e(*iterator);

    if (e.getNext()) {
        e.getNext()->setPrev(e.getPrev());
    } else {
        last = e.getPrev();
    }
    if (e.getPrev()) {
        e.getPrev()->setNext(e.getNext());
    } else {
        first = e.getNext();
    }

    delete iterator.getPointer();
    return e.getContent();
}


template<class T>
void list<T>::dropIf(bool (*predicate)(const T&)) {
    auto it = begin();
    while (it != end()) {
        auto tmp = it++;
        if (f(*tmp)) {
            drop(tmp);
        }
    }
}


template<class T>
void list<T>::wipe() {
    auto it = begin();
    while (it != end()) {
        auto tmp = it++;
        delete tmp.getPointer();
    }
    first = nullptr;
    last = nullptr;
}


template<class T>
iterator<T> list<T>::begin() const {
    return iterator<T>(first);
}


template<class T>
iterator<T> list<T>::end() const {
    return iterator<T>(nullptr);
}


template<class T>
T &list<T>::operator[](int n) {
    iterator<T> it(first);
    return *(it + n);
}


template<class T>
list<T>& list<T>::operator=(const list& l) {
    if (this == &l) {
        return *this;
    }
    wipe();
    for (const auto& e : l) {
        append(e);
    }
}

#endif //ARDUI_SLIST_H
