//
// Created by MStefan99 on 25.11.19.
//

#ifndef ARDUI_SLIST_H
#define ARDUI_SLIST_H


namespace ardui {
    template<class T>
    class list {
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

            friend class list;

        private:
            explicit iterator(element* elementPointer);
            list<T>::element* elementPointer;
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
        class element {
        public:
            explicit element(const T& value, element* prev = nullptr, element* next = nullptr);
            element(const element& listElement) = default;
            ~element() = default;

            element* getNext() const;
            element* getPrev() const;
            T& getValue();

            void setNext(element* next);
            void setPrev(element* prev);
            void setValue(const T& value);

            element& operator=(const element& listElement) = default;
            element& operator=(const T& value);

        private:
            T elementvalue;
            element* nextElement {nullptr};
            element* prevElement {nullptr};
        };

        element* first {nullptr};
        element* last {nullptr};

        void destroyElement(element* e);
        int listSize {0};
    };


    template <class T>
    list<T>::element::element(const T& value, element* prev, element* next):
            elementvalue(value), prevElement(prev), nextElement(next) {}


    template<class T>
    list<T>::list(const list& l) {
        for (const auto& e : l) {
            push_back(e);
        }
        listSize = l.size();
    }


    template<class T>
    list<T>::~list() {
        clear();
    }


    template<class T>
    void list<T>::push_back(const T &value) {
        auto e = new element(value, last);

        if (!first) {
            first = e;
        }
        if (last) {
            last->setNext(e);
        }
        last = e;
        ++listSize;
    }


    template<class T>
    void list<T>::push_front(const T &value) {
        auto e = new element(value, nullptr, first);

        if (!last) {
            last = e;
        }
        if (first) {
            first->setPrev(e);
        }
        first = e;
        ++listSize;
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
            --listSize;
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
            --listSize;
            delete e;
        }
    }


    template <class T>
    T& list<T>::front() const {
        return first->getValue();
    }


    template <class T>
    T& list<T>::back() const {
        return last->getValue();
    }


    template <class T>
    void list<T>::destroyElement(list<T>::element* e) {
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
        auto n = new element(value, nullptr, e);

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
        ++listSize;
        return iterator(n);
    }


    template<class T>
    typename list<T>::iterator list<T>::erase(iterator position) {
        auto temp = position;

        ++position;
        destroyElement(temp.elementPointer);
        --listSize;
        return position;
    }


    template<class T>
    typename list<T>::iterator list<T>::erase(iterator f, iterator l) {
        while (f != l) {
            auto temp {f};
            ++f;
            destroyElement(temp.elementPointer);
            --listSize;
        }
        return l;
    }


    template<class T>
    int list<T>::remove(const T& value) {
        int i {0};
        element* e {first};

        while (e) {
            auto temp = e;
            e = e->getNext();
            if (temp->getValue() == value) {
                destroyElement(temp);
                ++i;
                --listSize;
            }
        }
        return i;
    }


    template<class T>
    int list<T>::remove_if(bool (*p)(const T&)) {
        int i {0};
        element* e {first};

        while (e) {
            auto temp = e;
            e = e->getNext();
            if (p(temp->getValue())) {
                destroyElement(temp);
                ++i;
                --listSize;
            }
        }
        return i;
    }


    template<class T>
    void list<T>::clear() {
        element* e {first};

        while (e) {
            auto temp = e;
            e = e->getNext();
            destroyElement(temp);
            listSize = 0;
        }
    }


    template<class T>
    int list<T>::size() const {
        return listSize;
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
        return p->getValue();
    }


    template<class T>
    list<T>& list<T>::operator=(const list& l) {
        if (this == &l) {
            return *this;
        }
        clear();
        for (auto p = l.first; p != nullptr; p = p->getNext()) {
            push_back(p->getValue());
        }
    }


    template <class T>
    typename list<T>::element *list<T>::element::getNext() const {
        return nextElement;
    }


    template <class T>
    typename list<T>::element *list<T>::element::getPrev() const {
        return prevElement;
    }


    template <class T>
    T& list<T>::element::getValue() {
        return elementvalue;
    }


    template <class T>
    void list<T>::element::setNext(element *next) {
        nextElement = next;
    }


    template <class T>
    void list<T>::element::setPrev(element *prev) {
        prevElement = prev;
    }


    template <class T>
    void list<T>::element::setValue(const T& value) {
        elementvalue = value;
    }


    template <class T>
    typename list<T>::element& list<T>::element::operator=(const T& value) {
        elementvalue = value;
        return *this;
    }


    template <class T>
    list<T>::iterator::iterator(element* elementPointer): elementPointer(elementPointer) {}


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
        return &elementPointer->getValue();
    }


    template<class T>
    T& list<T>::iterator::operator*() const {
        return elementPointer->getValue();
    }
}

#endif //ARDUI_SLIST_H
