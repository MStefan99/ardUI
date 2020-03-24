//
// Created by MStefan99 on 29.1.20.
//

#ifndef ARDUI_TEST_MAP_H
#define ARDUI_TEST_MAP_H


#include "pair.h"
#include "less.h"
#include "stack.h"


template <class pNode>
pNode leftmost(pNode pointer) {
    if (pointer) {
        while (pointer->left) {
            pointer = pointer->left;
        }
    }
    return pointer;
}


template <class pNode>
pNode rightmost(pNode pointer) {
    if (pointer) {
        while (pointer->right) {
            pointer = pointer->right;
        }
    }
    return pointer;
}


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
            explicit iterator(element* currentElement, element* lastElement = nullptr);
            element* currentElement {nullptr};
            element* lastElement {nullptr};
        };

        map() = default;
        ~map();

        T& operator[](const Key& k);

        bool empty() const;
        int size() const;

        iterator find(const Key& k) const;

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
        void unlinkElement(element* e);
        element* findElement(const Key& k) const;

        element* mapRoot {nullptr};
        Comp less {};
        int mapSize {0};
        bool balancingLeft {true};
    };


    template<class Key, class T, class Comp>
    map<Key, T, Comp>::iterator::iterator(element *currentElement, element* lastElement):
            currentElement(currentElement),
            lastElement(lastElement) {
    }


    template<class Key, class T, class Comp>
    typename map<Key, T, Comp>::iterator &map<Key, T, Comp>::iterator::operator++() {
        if (currentElement->right) {
            currentElement = leftmost(currentElement->right);
            lastElement = currentElement;
        } else if (currentElement->parent) {
            while (currentElement->parent && currentElement->parent->right == currentElement) {
                currentElement = currentElement->parent;
            }
            if (currentElement->parent) {
                currentElement = currentElement->parent;
            } else {
                currentElement = nullptr;
            }
        }
        return *this;
    }


    template<class Key, class T, class Comp>
    const typename map<Key, T, Comp>::iterator map<Key, T, Comp>::iterator::operator++(int) { // NOLINT(readability-const-return-type)
        auto temp {*this};
        if (currentElement->right) {
            currentElement = leftmost(currentElement->right);
            lastElement = currentElement;
        } else if (currentElement->parent) {
            while (currentElement->parent && currentElement->parent->right == currentElement) {
                currentElement = currentElement->parent;
            }
            if (currentElement->parent) {
                currentElement = currentElement->parent;
            } else {
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
            currentElement = rightmost(currentElement->left);
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
            currentElement = rightmost(currentElement->left);
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
    typename map<Key, T, Comp>::iterator map<Key, T, Comp>::find(const Key& k) const {
        return iterator(findElement(k));
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
        auto temp {position};
        ++position;
        unlinkElement(temp.currentElement);
        delete (temp.currentElement);
        --mapSize;

        return position;
    }


    template<class Key, class T, class Comp>
    int map<Key, T, Comp>::erase(const Key& k) {
        element* e {findElement(k)};

        if (e) {
            unlinkElement(e);
            delete e;
            --mapSize;
            return 1;
        } else {
            return 0;
        }
    }


    template<class Key, class T, class Comp>
    typename map<Key, T, Comp>::iterator map<Key, T, Comp>::erase(iterator first, iterator last) {
        while (first != last) {  // TODO: fix
            auto temp {first};
            ++first;
            unlinkElement(temp.currentElement);
            delete (temp.currentElement);
            --mapSize;
        }
        return last;
    }


    template<class Key, class T, class Comp>
    void map<Key, T, Comp>::clear() {
        erase(begin(), end());  // TODO: remove iterators
    }

    template<class Key, class T, class Comp>
    map<Key, T, Comp>::~map() {
        clear();
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
        return map::iterator(leftmost(mapRoot));
    }


    template<class Key, class T, class Comp>
    typename map<Key, T, Comp>::iterator map<Key, T, Comp>::end() const {
        return map::iterator(nullptr, rightmost(mapRoot));
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
    void map<Key, T, Comp>::unlinkElement(element* e) {
        element* replacement {};

        if (e->left && e->right) {
            if (balancingLeft) {
                replacement = rightmost(e->left);
                replacement->right = e->right;
            } else {
                replacement = leftmost(e->right);
                replacement->left = e->left;
            }
            balancingLeft = !balancingLeft;
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


    template<class Key, class T, class Comp>
    typename map<Key, T, Comp>::element* map<Key, T, Comp>::findElement(const Key& k) const {
        element* node {mapRoot};

        while (node) {
            if (less(k, node->value.first)) {
                node = node->left;
            } else if (less(node->value.first, k)) {
                node = node->right;
            } else {
                return node;
            }
        }
        return nullptr;
    }
}


#endif //ARDUI_TEST_MAP_H
