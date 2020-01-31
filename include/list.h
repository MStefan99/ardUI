//
// Created by MStefan99 on 25.11.19.
//

#ifndef ARDUI_SLIST_H
#define ARDUI_SLIST_H

namespace ardui {
    template<class T>
    class list {
    protected:
        class listElement;

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

            friend class list;

        private:
            explicit iterator(listElement* elementPointer);
            list<T>::listElement* elementPointer;
        };

        list() = default;
        list(const list& list);
        ~list();

        void push_back(const T &value);
        void push_front(const T &value);

        T& front() const;
        T& back() const;

        void pop_back();
        void pop_front();

        int remove(const T& value);
        int remove_if(bool (*predicate)(const T&));

        iterator insert(iterator position, const T& value);

        iterator erase(iterator position);
        iterator erase(iterator first, iterator last);
        void clear();

        int size() const;
        bool empty() const;

        T& operator[](int n) const;
        list& operator=(const list& list);

        iterator begin() const;
        iterator end() const;

    protected:
        class listElement {
        public:
            explicit listElement(const T& value, listElement* prev = nullptr, listElement* next = nullptr);
            listElement(const listElement& listElement) = default;
            ~listElement() = default;

            listElement* getNext() const;
            listElement* getPrev() const;
            T& getValue();

            void setNext(listElement* next);
            void setPrev(listElement* prev);
            void setValue(const T& value);

            listElement& operator=(const listElement& listElement) = default;
            listElement& operator=(const T& value);

        private:
            T elementvalue;
            listElement* nextElement {nullptr};
            listElement* prevElement {nullptr};
        };

        listElement* first {nullptr};
        listElement* last {nullptr};

        void removeElement(listElement* e);
    };


    template <class T>
    list<T>::listElement::listElement(const T& value, listElement* prev, listElement* next):
            elementvalue(value), prevElement(prev), nextElement(next) {}


    template<class T>
    list<T>::list(const list& l) {
        for (const auto& e : l) {
            push_back(e);
        }
    }


    template<class T>
    list<T>::~list() {
        clear();
    }


    template<class T>
    void list<T>::push_back(const T &value) {
        auto e = new listElement(value, last);

        if (!first) {
            first = e;
        }
        if (last) {
            last->setNext(e);
        }
        last = e;
    }


    template<class T>
    void list<T>::push_front(const T &value) {
        auto e = new listElement(value, nullptr, first);

        if (!last) {
            last = e;
        }
        if (first) {
            first->setPrev(e);
        }
        first = e;
    }


    template<class T>
    void list<T>::pop_back() {
        auto e {last};
        if (e) {
            auto value {last->getvalue()};

            if (e->getPrev()) {
                e->getPrev()->setNext(nullptr);
            } else {
                first = nullptr;
            }

            last = e->getPrev();
            delete e;
        }
    }


    template<class T>
    void list<T>::pop_front() {
        auto e {first};
        if (e) {
            auto value {first->getvalue()};

            if (e->getNext()) {
                e->getNext()->setPrev(nullptr);
            } else {
                last = nullptr;
            }

            first = e->getNext();
            delete e;
        }
    }


    template <class T>
    T& list<T>::front() const {
        return first->getvalue();
    }


    template <class T>
    T& list<T>::back() const {
        return last->getvalue();
    }


    template <class T>
    void list<T>::removeElement(list<T>::listElement* e) {
        if (e->getNext()) {
            e->getNext()->setPrev(e->getPrev());
        } else {
            last = e->getPrev();
        }
        if (e->getPrev()) {
            e->getPrev()->setNext(e->getNext());
        } else {
            first = e->getNext();
        }
        delete e;
    }


    template<class T>
    typename list<T>::iterator list<T>::insert(iterator position, const T& value) {
        auto e {position.elementPointer};
        auto n = new listElement(value, nullptr, e);

        if (e) {
            if (e->getPrev()) {
                n->setPrev(e->getPrev());
                e->getPrev()->setNext(n);
            } else {
                first = n;
            }
            e->setPrev(n);
        } else {
            if (!first) {
                first = n;
            }
            if (last) {
                last->setNext(n);
                n->setPrev(last);
            }
            last = n;
        }
        return iterator(n);
    }


    template<class T>
    typename list<T>::iterator list<T>::erase(iterator position) {
        removeElement(&(*position));
        return ++position;
    }


    template<class T>
    typename list<T>::iterator list<T>::erase(iterator f, iterator l) {
        while (f != l) {
            removeElement(&(*f));
            ++l;
        }
        return l;
    }


    template<class T>
    int list<T>::remove(const T& value) {
        int i {0};
        listElement* e {first};

        while (e) {
            auto temp = e;
            e = e->getNext();
            if (temp->getvalue() == value) {
                removeElement(temp);
            }
        }
        return i;
    }


    template<class T>
    int list<T>::remove_if(bool (*p)(const T&)) {
        int i {0};
        listElement* e {first};

        while (e) {
            auto temp = e;
            e = e->getNext();
            if (p(temp->getvalue())) {
                removeElement(temp);
            }
        }
        return i;
    }


    template<class T>
    void list<T>::clear() {
        listElement* e {first};

        while (e) {
            auto temp = e;
            e = e->getNext();
            removeElement(temp);
        }
    }


    template<class T>
    int list<T>::size() const {
        int i {0};

        for (listElement* e {first}; e; e = e->getNext()) {
            ++i;
        }
        return i;
    }


    template <class T>
    bool list<T>::empty() const {
        return first == nullptr;
    }


    template<class T>
    typename list<T>::iterator list<T>::begin() const {
        return iterator(first);
    }


    template<class T>
    typename list<T>::iterator list<T>::end() const {
        return iterator(nullptr);
    }


    template<class T>
    T &list<T>::operator[](int n) const {
        auto p {first};
        for (int i {0}; i < n; ++i) {
            p = p->getNext();
        }
        return p->getvalue();
    }


    template<class T>
    list<T>& list<T>::operator=(const list& l) {
        if (this == &l) {
            return *this;
        }
        clear();
        for (auto p = l.first; p != nullptr; p = p->getNext()) {
            push_back(p->getvalue());
        }
    }


    template <class T>
    typename list<T>::listElement *list<T>::listElement::getNext() const {
        return nextElement;
    }


    template <class T>
    typename list<T>::listElement *list<T>::listElement::getPrev() const {
        return prevElement;
    }


    template <class T>
    T& list<T>::listElement::getValue() {
        return elementvalue;
    }


    template <class T>
    void list<T>::listElement::setNext(listElement *next) {
        nextElement = next;
    }


    template <class T>
    void list<T>::listElement::setPrev(listElement *prev) {
        prevElement = prev;
    }


    template <class T>
    void list<T>::listElement::setValue(const T& value) {
        elementvalue = value;
    }


    template <class T>
    typename list<T>::listElement& list<T>::listElement::operator=(const T& value) {
        elementvalue = value;
        return *this;
    }


    template <class T>
    list<T>::iterator::iterator(listElement* elementPointer): elementPointer(elementPointer) {}


    template<class T>
    typename list<T>::iterator &list<T>::iterator::operator++() {
        elementPointer = elementPointer->getNext();
        return *this;
    }


    template<class T>
    const typename list<T>::iterator list<T>::iterator::operator++(int) { // NOLINT(readability-const-return-type)
        iterator temp {*this};
        elementPointer = elementPointer->getNext();
        return temp;
    }


    template<class T>
    typename list<T>::iterator &list<T>::iterator::operator--() {
        elementPointer = elementPointer->getPrev();
        return *this;
    }


    template<class T>
    const typename list<T>::iterator list<T>::iterator::operator--(int) { // NOLINT(readability-const-return-type)
        iterator temp {this};
        elementPointer = elementPointer->getPrev();
        return temp;
    }


    template<class T>
    bool list<T>::iterator::operator==(const iterator& it) const {
        return elementPointer == it.elementPointer;
    }


    template<class T>
    bool list<T>::iterator::operator!=(const iterator& it) const {
        return elementPointer != it.elementPointer;
    }


    template<class T>
    typename list<T>::iterator& list<T>::iterator::operator=(const T& value) {
        elementPointer->setvalue(value);
        return *this;
    }


    template<class T>
    T* list<T>::iterator::operator->() const {
        return &elementPointer->getvalue();
    }


    template<class T>
    T& list<T>::iterator::operator*() const {
        return elementPointer->getvalue();
    }
}

#endif //ARDUI_SLIST_H
