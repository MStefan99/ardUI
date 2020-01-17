//
// Created by MStefan99 on 25.11.19.
//

#ifndef ARDUI_SLIST_H
#define ARDUI_SLIST_H


template<class T>
class list {
public:
    class listIterator {
        
    };
    
    list() = default;
    list(const list& list);
    ~list();

    void pushBack(const T &content);
    void pushFront(const T &content);

    T popBack();
    T popFront();

    int remove(const T& content);
    int removeIf(bool (*predicate)(const T&));

    void clear();
    void erase(listIterator iterator);
    int length();

    T& operator[](int n);
    list& operator=(const list& list);

    listIterator begin() const;
    listIterator end() const;

protected:
    class listElement {
    public:
        explicit listElement(const T& content, listElement* prev = nullptr, listElement* next = nullptr);
        listElement(const listElement& listElement) = default;
        ~listElement();

        listElement* getNext() const;
        listElement* getPrev() const;
        T& getContent();

        void setNext(listElement* next);
        void setPrev(listElement* prev);

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
        pushBack(e);
    }
}


template<class T>
list<T>::~list() {
    clear();
}


template<class T>
void list<T>::pushBack(const T &content) {
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
void list<T>::pushFront(const T &content) {
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
T list<T>::popBack() {
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
        return content;
    } else {
        return T{};  //TODO: handle exception
    }
}


template<class T>
T list<T>::popFront() {
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
        return content;
    } else {
        return T{};  //TODO: handle exception
    }
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
void list<T>::erase(listIterator iterator) {
    auto e {*iterator.getPointer()};

    removeElement(e);
}


template<class T>
int list<T>::remove(const T& content) {
    int i {0};

    for (listElement* e {first}; e->getNext(); e = e->getNext()) {
        if (e->getContent() == content) {
            removeElement(e);
            ++i;
        }
    }
    return i;
}


template<class T>
int list<T>::removeIf(bool (*p)(const T&)) {
    int i {0};

    for (listElement* e {first}; e->getNext(); e = e->getNext()) {
        if (p(e->getContent())) {
            removeElement(e);
            ++i;
        }
    }
    return i;
}


template<class T>
void list<T>::clear() {
    if (first) {
        for (listElement *e{first}; e->getNext(); e = e->getNext()) {
            removeElement(e);
        }
    }
}


template<class T>
int list<T>::length() {
    int i {0};

    for (listElement* e {first}; e->getNext(); e = e->getNext()) {
        ++i;
    }
    return i;
}


template<class T>
typename list<T>::listIterator list<T>::begin() const {
    return listIterator(first);
}


template<class T>
typename list<T>::listIterator list<T>::end() const {
    return listIterator(nullptr);
}


template<class T>
T &list<T>::operator[](int n) {
    listIterator it(first);
    return *(it + n);
}


template<class T>
list<T>& list<T>::operator=(const list& l) {
    if (this == &l) {
        return *this;
    }
    clear();
    for (const auto& e : l) {
        pushBack(e);
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
typename list<T>::listElement& list<T>::listElement::operator=(const T& content) {
    elementContent = content;
    return *this;
}


template <class T>
list<T>::listElement::~listElement() {

}

#endif //ARDUI_SLIST_H
