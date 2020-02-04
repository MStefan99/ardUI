//
// Created by MStefan99 on 29.1.20.
//

#ifndef ARDUI_TEST_MAP_H
#define ARDUI_TEST_MAP_H


#include "pair.h"
#include "less.h"
#include "stack.h"


namespace ardui {
    template <class Key, class T, class Comp = less<T>>
    class map {
    protected:
        class element;

    public:
        class iterator {  // bidirectional iterator
        public:
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
            stack<element*> s;
        };

        map() = default;
        ~map() = default;

        element operator[](const Key& k);

        bool empty() const;
        int size() const;

        pair<iterator, bool> insert(const T& value);

        iterator erase(iterator position);
        iterator erase(iterator first, iterator last);
        int erase(const Key& k);

        void clear();

        iterator begin() const;
        iterator end() const;

    protected:
        class element {
        public:
            element() = default;

        private:
            pair<Key, T> value;
            element* left {nullptr};
            element* right {nullptr};
        };

        element* mapRoot {nullptr};
        int mapSize {0};
    };
    
}

#endif //ARDUI_TEST_MAP_H
