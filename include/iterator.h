//
// Created by MStefan99 on 25.11.19.
//

#ifndef ARDUI_ITERATOR_H
#define ARDUI_ITERATOR_H

#include "element.h"

template<class T>
class iterator {
public:
    explicit iterator(element<T> *elementPtr);

    iterator operator+(int n);
    iterator &operator++();
    const iterator operator++(int);

    iterator operator-(int n);
    iterator &operator--();
    const iterator<T> operator--(int);

    bool operator==(iterator it);
    bool operator!=(iterator it);

    element<T> *operator[](int n);

    T &operator*();

    explicit operator bool();
    explicit operator element<T> *();

    element<T> *getPointer();
private:
    element<T>* pointer {nullptr};
};


template<class T>
iterator<T>::iterator(element<T> *elementPtr): pointer(elementPtr) {}


template<class T>
iterator<T> iterator<T>::operator+(int n) {
    auto it = *this;
    for (int i = 0; i < n; ++i) {
        ++it;
    }
    return it;
}


template<class T>
iterator<T> &iterator<T>::operator++() {
    if (pointer) {
        pointer = pointer->getNext();
    } else {
        //TODO: handle Exception
    }
    return *this;
}


template<class T>
const iterator<T> iterator<T>::operator++(int) { // NOLINT(readability-const-return-type)
    auto temp = iterator(*this);
    if (pointer) {
        pointer = pointer->getNext();
    } else {
        //TODO: handle Exception
    }
    return temp;
}


template<class T>
iterator<T> iterator<T>::operator-(int n) {
    auto it = *this;
    for (int i = 0; i < n; ++i) {
        --it;
    }
    return it;
}


template<class T>
iterator<T> &iterator<T>::operator--() {
    if (pointer) {
        pointer = pointer->getPrev();
    } else {
        //TODO: handle Exception
    }
    return *this;
}


template<class T>
const iterator<T> iterator<T>::operator--(int) { // NOLINT(readability-const-return-type)
    auto temp = iterator(*this);
    if (pointer) {
        pointer = pointer->getPrev();
    } else {
        //TODO: handle Exception
    }
    return temp;
}


template<class T>
bool iterator<T>::operator==(iterator<T> it) {
    return pointer == it.pointer;
}


template<class T>
bool iterator<T>::operator!=(iterator<T> it) {
    return pointer != it.pointer;
}


template<class T>
element<T> *iterator<T>::operator[](int n) {
    return this + n;
}


template<class T>
T &iterator<T>::operator*() {
    if (pointer) {
        return pointer->getContent();
    } else {
        //TODO: handle Exception (Important: control reaches end)
    }
}


template<class T>
iterator<T>::operator bool() {
    return pointer;
}


template<class T>
iterator<T>::operator element<T> *() {
    return pointer;
}


template<class T>
element<T> *iterator<T>::getPointer() {
    return pointer;
}


#endif //ARDUI_ITERATOR_H
