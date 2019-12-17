//
// Created by MStefan99 on 25.11.19.
//

#ifndef ARDUI_ELEMENT_H
#define ARDUI_ELEMENT_H

template <class T>
class element {
public:
    explicit element(const T& content);
    element(const element& element) = default;
    explicit element(const T& content, element* prev = nullptr, element* next = nullptr);

    element* getNext() const;
    element* getPrev() const;
    T& getContent();

    void setNext(element*);
    void setPrev(element*);

    element& operator=(const element& element);
    element& operator=(const T& content);

    explicit operator const T&() const;
private:
    T content;
    element* next {nullptr};
    element* prev {nullptr};
};


template<class T>
element<T>::element(const T &content): content(content) {}


template<class T>
element<T>::element(const T &content, element *prev, element *next): content(content), next(next), prev(prev) {}


template<class T>
element<T> *element<T>::getNext() const {
    return next;
}


template<class T>
element<T> *element<T>::getPrev() const {
    return prev;
}


template<class T>
T &element<T>::getContent() {
    return content;
}


template<class T>
void element<T>::setNext(element *pElement) {
    next = pElement;
}


template<class T>
void element<T>::setPrev(element *pElement) {
    prev = pElement;
}


template<class T>
element<T>& element<T>::operator=(const element &element) {
    if (element != this) {
        prev = element.prev;
        next = element.next;
        content = element.content;
    }
    return *this;
}


template <class T>
element<T>& element<T>::operator=(const T& c) {
    content = c;
}


template<class T>
element<T>::operator const T&() const {
    return content;
}


#endif //ARDUI_ELEMENT_H