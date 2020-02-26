//
// Created by MStefan99 on 29.1.20.
//

#ifndef ARDUI_TEST_MAP_H
#define ARDUI_TEST_MAP_H


#include "pair.h"
#include "less.h"
#include "stack.h"


#define MOVE_TO_LEFTMOST_NODE(pointer) \
        if (pointer) {\
            while (pointer->left) {\
                pointer = pointer->left;\
            }\
        }\


#define MOVE_TO_RIGHTMOST_NODE(pointer) \
        if (pointer) {\
            while (pointer->right) {\
                pointer = pointer->right;\
            }\
        }\


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

            pair<const Key, T>* operator->() const;
            pair<const Key, T>& operator*() const;

            friend class map;

        private:
            explicit iterator(element* elementPointer);
            iterator(element* currentElement, element* lastElement);
            element* currentElement {nullptr};
            element* lastElement {nullptr};

            bool leftDone {false};
            bool rightDone {false};
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
            explicit element(const pair<const Key, T>& value, element* parent);
            explicit element(const Key& k, element* parent);

            pair<const Key, T> value;
            element* parent;
            element* left {nullptr};
            element* right {nullptr};
        };

        void replaceElement(element* o, element* n);
        void deleteElement(element* e);
        element* mapRoot {nullptr};
        Comp less {};
        int mapSize {0};
        bool balancingLeft {true};
    };


    template<class Key, class T, class Comp>
    map<Key, T, Comp>::iterator::iterator(element *elementPointer):
            currentElement(elementPointer) {
    }


    template<class Key, class T, class Comp>
    map<Key, T, Comp>::iterator::iterator(element *currentElement, element* lastElement):
            currentElement(currentElement),
            lastElement(lastElement) {
    }


    template<class Key, class T, class Comp>
    typename map<Key, T, Comp>::iterator &map<Key, T, Comp>::iterator::operator++() {
        if (currentElement->right) {
            currentElement = currentElement->right;
            MOVE_TO_LEFTMOST_NODE(currentElement);
        } else if (currentElement->parent) {
            while (currentElement->parent && currentElement->parent->right == currentElement) {
                currentElement = currentElement->parent;
            }
            if (currentElement->parent) {
                currentElement = currentElement->parent;
            } else {
                lastElement = currentElement;  // TODO: fix
                currentElement = nullptr;
            }
        }
        return *this;
    }


    template<class Key, class T, class Comp>
    const typename map<Key, T, Comp>::iterator map<Key, T, Comp>::iterator::operator++(int) { // NOLINT(readability-const-return-type)
        auto temp {*this};
        if (currentElement->right) {
            currentElement = currentElement->right;
            MOVE_TO_LEFTMOST_NODE(currentElement);
        } else if (currentElement->parent) {
            while (currentElement->parent && currentElement->parent->right == currentElement) {
                currentElement = currentElement->parent;
            }
            if (currentElement->parent) {
                currentElement = currentElement->parent;
            } else {
                lastElement = currentElement;  // TODO: fix
                currentElement = nullptr;
            }
        }
        return temp;
    }


    template<class Key, class T, class Comp>
    typename map<Key, T, Comp>::iterator &map<Key, T, Comp>::iterator::operator--() {
        if (!currentElement) {
            currentElement = lastElement;
        } else if (currentElement->left) {
            currentElement = currentElement->left;
            MOVE_TO_RIGHTMOST_NODE(currentElement);
        } else if (currentElement->parent) {
            while (currentElement->parent && currentElement->parent->left == currentElement) {
                currentElement = currentElement->parent;
            }
            if (currentElement->parent) {
                currentElement = currentElement->parent;
            }
        }
        return *this;
    }


    template<class Key, class T, class Comp>
    const typename map<Key, T, Comp>::iterator map<Key, T, Comp>::iterator::operator--(int) { // NOLINT(readability-const-return-type)
        auto temp {*this};
        if (!currentElement) {
            currentElement = lastElement;
        } else if (currentElement->left) {
            currentElement = currentElement->left;
            MOVE_TO_RIGHTMOST_NODE(currentElement);
        } else if (currentElement->parent) {
            while (currentElement->parent && currentElement->parent->left == currentElement) {
                currentElement = currentElement->parent;
            }
            if (currentElement->parent) {
                currentElement = currentElement->parent;
            }
        }
        return temp;
    }


    template<class Key, class T, class Comp>
    bool map<Key, T, Comp>::iterator::operator==(const iterator &it) const {
        return currentElement == it.currentElement;
    }


    template<class Key, class T, class Comp>
    bool map<Key, T, Comp>::iterator::operator!=(const iterator &it) const {
        return currentElement != it.currentElement;
    }


    template<class Key, class T, class Comp>
    typename map<Key, T, Comp>::iterator &map<Key, T, Comp>::iterator::operator=(const T& value) {
        currentElement->value.second = value;
        return *this;
    }


    template<class Key, class T, class Comp>
    pair<const Key, T> *map<Key, T, Comp>::iterator::operator->() const {
        return &currentElement->value;
    }


    template<class Key, class T, class Comp>
    pair<const Key, T> &map<Key, T, Comp>::iterator::operator*() const {
        return currentElement->value;
    }


    template<class Key, class T, class Comp>
    map<Key, T, Comp>::element::element(const pair<const Key, T> &value, element* parent):
            value(value),
            parent(parent) {
    }


    template<class Key, class T, class Comp>
    map<Key, T, Comp>::element::element(const Key& k, element* parent):
            value(k, T{}),
            parent(parent) {
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
        element** parent {&mapRoot};

        while (*node) {
            Key k = (*node)->value.first;
            if (k == value.first) {
                return {iterator(*node), false};
            } else if (less(value.first, k)) {
                parent = node;
                node = &(*node)->left;
            } else {
                parent = node;
                node = &(*node)->right;
            }
        }
        ++mapSize;
        *node = new element {value, *parent};
        return {iterator(*node), true};
    }


    template<class Key, class T, class Comp>
    typename map<Key, T, Comp>::iterator map<Key, T, Comp>::erase(iterator position) {
        deleteElement(position.currentElement);
        auto it {position};
        ++it;
        delete position.currentElement;

        return it;
    }


    template<class Key, class T, class Comp>
    T &map<Key, T, Comp>::operator[](const Key &k) {
        element** node {&mapRoot};
        element** parent {&mapRoot};

        while (*node) {
            Key cKey = (*node)->value.first;
            if (cKey == k) {
                return (*node)->value.second;
            } else if (less(k, cKey)) {
                parent = node;
                node = &(*node)->left;
            } else {
                parent = node;
                node = &(*node)->right;
            }
        }
        ++mapSize;
        *node = new element {k, *parent};
        return (*node)->value.second;
    }


    template<class Key, class T, class Comp>
    typename map<Key, T, Comp>::iterator map<Key, T, Comp>::begin() const {
        auto p {mapRoot};
        MOVE_TO_LEFTMOST_NODE(p);
        return map::iterator(p);
    }


    template<class Key, class T, class Comp>
    typename map<Key, T, Comp>::iterator map<Key, T, Comp>::end() const {
        auto p {mapRoot};
        MOVE_TO_RIGHTMOST_NODE(p);
        return map::iterator(nullptr, p);
    }


    template<class Key, class T, class Comp>
    void map<Key, T, Comp>::replaceElement(element *o, element *n) {
        if (o->parent) {
            if (o == o->parent->left) {
                o->parent->left = n;
            } else {
                o->parent->right = n;
            }
            if (n->parent) {
                n->parent = o->parent;
            }
        }
    }


    template<class Key, class T, class Comp>
    void map<Key, T, Comp>::deleteElement(element* e) {
        element* replacement {};

        if (e->left && e->right) {
            if (balancingLeft) {
                replacement = e->left;
                MOVE_TO_RIGHTMOST_NODE(replacement);
                replacement->right = e->right;
            } else {
                replacement = e->right;
                MOVE_TO_LEFTMOST_NODE(replacement);
                replacement->left = e->left;
            }
            replaceElement(e, replacement);
        } else if (e->left) {
            replaceElement(e, e->left);
        } else if (e->right) {
            replaceElement(e, e->right);
        } else {
            if (e->parent->left == e) {
                e->parent->left = nullptr;
            } else {
                e->parent->right = nullptr;
            }
        }
    }
}


#endif //ARDUI_TEST_MAP_H
