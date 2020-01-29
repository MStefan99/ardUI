//
// Created by MStefan99 on 25.11.19.
//

#ifndef ARDUI_SLIST_H
#define ARDUI_SLIST_H


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

    void push_back(const T &content);
    void push_front(const T &content);

    T& front() const;
    T& back() const;

    void pop_back();
    void pop_front();

    int remove(const T& content);
    int remove_if(bool (*predicate)(const T&));

    void clear();
    void erase(iterator position);
    void erase(iterator first, iterator last);

    int size() const;
    bool empty() const;

    T& operator[](int n) const;
    list& operator=(const list& list);

    iterator begin() const;
    iterator end() const;

protected:
    class listElement {
    public:
        explicit listElement(const T& content, listElement* prev = nullptr, listElement* next = nullptr);
        listElement(const listElement& listElement) = default;
        ~listElement() = default;

        listElement* getNext() const;
        listElement* getPrev() const;
        T& getContent();

        void setNext(listElement* next);
        void setPrev(listElement* prev);
        void setContent(const T& content);

        listElement& operator=(const listElement& listElement) = default;
        listElement& operator=(const T& content);

    private:
        T elementContent;
        listElement* nextElement {nullptr};
        listElement* prevElement {nullptr};
    };

    listElement* first {nullptr};
    listElement* last {nullptr};

    void removeElement(listElement* e);
};


template <class T>
list<T>::listElement::listElement(const T& content, listElement* prev, listElement* next):
        elementContent(content), prevElement(prev), nextElement(next) {}


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
void list<T>::push_back(const T &content) {
    auto e = new listElement(content, last);

    if (!first) {
        first = e;
    }
    if (last) {
        last->setNext(e);
    }
    last = e;
}


template<class T>
void list<T>::push_front(const T &content) {
    auto e = new listElement(content, nullptr, first);

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
        auto content {last->getContent()};

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
        auto content {first->getContent()};

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
    return first->getContent();
}


template <class T>
T& list<T>::back() const {
    return last->getContent();
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
void list<T>::erase(iterator position) {
    removeElement(&(*position));
}


template<class T>
void list<T>::erase(iterator f, iterator l) {
    while (f != l) {
        removeElement(&(*f));
        ++l;
    }
}


template<class T>
int list<T>::remove(const T& content) {
    int i {0};
    listElement* e {first};

    while (e) {
        auto temp = e;
        e = e->getNext();
        if (temp->getContent() == content) {
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
        if (p(temp->getContent())) {
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
    iterator it(first);  // TODO: rewrite using list traversal
    return *it;
}


template<class T>
list<T>& list<T>::operator=(const list& l) {
    if (this == &l) {
        return *this;
    }
    clear();
    for (const auto& e : l) {  //TODO: rewrite using list traversal
        push_back(e);
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
T& list<T>::listElement::getContent() {
    return elementContent;
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
void list<T>::listElement::setContent(const T& content) {
    elementContent = content;
}


template <class T>
typename list<T>::listElement& list<T>::listElement::operator=(const T& content) {
    elementContent = content;
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
typename list<T>::iterator& list<T>::iterator::operator=(const T& content) {
    elementPointer->setContent(content);
    return *this;
}


template<class T>
T* list<T>::iterator::operator->() const {
    return &elementPointer->getContent();
}


template<class T>
T& list<T>::iterator::operator*() const {
    return elementPointer->getContent();
}


#endif //ARDUI_SLIST_H
