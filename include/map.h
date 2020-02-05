//
// Created by MStefan99 on 29.1.20.
//

#ifndef ARDUI_TEST_MAP_H
#define ARDUI_TEST_MAP_H


#include "pair.h"
#include "less.h"
#include "stack.h"


namespace ardui {
    template <class Key, class T, class Comp = less<Key>>
    class map {
    protected:
        struct element;

    public:
        class iterator {  // bidirectional iterator
        public:
            iterator() = default;

            iterator& operator++();
            const iterator operator++(int);

            iterator& operator--();
            const iterator operator--(int);

            bool operator==(const iterator& it) const;
            bool operator!=(const iterator& it) const;

            iterator& operator=(const T&);

            T* operator->() const;
            T& operator*() const;

            friend class map;

        private:
            explicit iterator(element* elementPointer);
            stack<element*> iteratorStack {};
            element* currentElement {nullptr};
        };

        map() = default;
        ~map() = default;

        T& operator[](const Key& k);

        bool empty() const;
        int size() const;

        pair<iterator, bool> insert(const pair<const Key, T>& value);  // Pair should be passed as argument

        iterator erase(iterator position);
        int erase(const Key& k);
        iterator erase(iterator first, iterator last);

        void clear();

        iterator begin() const;
        iterator end() const;

    protected:
        struct element {
            explicit element(const pair<const Key, T>& value);
            explicit element(const Key& k);

            pair<const Key, T> value;
            element* left {nullptr};
            element* right {nullptr};
        };

        element* mapRoot {nullptr};
        Comp less {};
        int mapSize {0};
        bool balancingLeft {true};
    };

    template<class Key, class T, class Comp>
    map<Key, T, Comp>::iterator::iterator(map::element *elementPointer) {
        iteratorStack.push(elementPointer);
    }


    template<class Key, class T, class Comp>
    map<Key, T, Comp>::element::element(const pair<const Key, T> &value): value(value) {
    }


    template<class Key, class T, class Comp>
    map<Key, T, Comp>::element::element(const Key& k): value(k, T{}) {
    }

    template<class Key, class T, class Comp>
    bool map<Key, T, Comp>::empty() const {
        return mapSize == 0;
    }


    template<class Key, class T, class Comp>
    int map<Key, T, Comp>::size() const {
        return mapSize;
    }


    template<class Key, class T, class Comp>
    pair<typename map<Key, T, Comp>::iterator, bool> map<Key, T, Comp>::insert(const pair<const Key, T>& value) {
        element** node {&mapRoot};

        while (*node) {
            Key k = (*node)->value.first;
            if (k == value.first) {
                return {iterator(*node), false};
            } else if (less(value.first, k)) {
                node = &(*node)->left;
            } else {
                node = &(*node)->right;
            }
        }
        *node = new element {value};
        return {iterator(*node), true};
    }


    template<class Key, class T, class Comp>
    T &map<Key, T, Comp>::operator[](const Key &k) {
        element** node {&mapRoot};

        while (*node) {
            Key cKey = (*node)->value.first;
            if (cKey == k) {
                return (*node)->value.second;
            } else if (less(k, cKey)) {
                node = &(*node)->left;
            } else {
                node = &(*node)->right;
            }
        }

        *node = new element {k};
        return (*node)->value.second;
    }
}

#endif //ARDUI_TEST_MAP_H
