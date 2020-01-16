//
// Created by MStefan99 on 25.11.19.
//

// An iterator implementation for a simple array.
// Inherit and override necessary methods for use in custom container.


#ifndef ARDUI_ITERATOR_H
#define ARDUI_ITERATOR_H


template<class T, class Pointer = T*, class Reference = T&>
class iterator {
public:
    iterator() = default;
    iterator(const iterator&) = default;
    virtual ~iterator() = default;

    virtual iterator& operator++();
    virtual const iterator operator++(int);

    virtual bool operator==(iterator) const;
    virtual bool operator!=(iterator it) const;

    virtual Pointer operator->() const;
    virtual Reference operator*() const;

    virtual iterator operator+(int n) const;
    virtual iterator operator-(int n) const;
    virtual Reference operator[](int n) const;  //TODO:
    virtual iterator& operator+=(int);
    virtual iterator& operator-=(int);

protected:
    Pointer mPointer {nullptr};
};


template <class T, class Pointer, class Reference>
iterator<T, Pointer, Reference> &iterator<T, Pointer, Reference>::operator++() {
    ++mPointer;
    return *this;
}


template <class T, class Pointer, class Reference>
const iterator<T, Pointer, Reference> iterator<T, Pointer, Reference>::operator++(int) { // NOLINT(readability-const-return-type)
    auto temp = iterator(*this);
    ++mPointer;
    return temp;
}


template<class T, class Pointer, class Reference>
bool iterator<T, Pointer, Reference>::operator==(iterator it) const {
    return mPointer == it.mPointer;
}


template<class T, class Pointer, class Reference>
bool iterator<T, Pointer, Reference>::operator!=(iterator it) const {
    return mPointer != it.mPointer;
}


template<class T, class Pointer, class Reference>
Pointer iterator<T, Pointer, Reference>::operator->() const {
    return mPointer;
}


template<class T, class Pointer, class Reference>
Reference iterator<T, Pointer, Reference>::operator*() const {
    return *mPointer;
}


template<class T, class Pointer, class Reference>
iterator<T, Pointer, Reference> iterator<T, Pointer, Reference>::operator+(int n) const {
    auto temp = iterator(*this);
    temp.mPointer += n;
    return temp;
}


template<class T, class Pointer, class Reference>
iterator<T, Pointer, Reference> iterator<T, Pointer, Reference>::operator-(int n) const {
    auto temp = iterator(*this);
    temp.mPointer -= n;
    return temp;
}


template<class T, class Pointer, class Reference>
Reference iterator<T, Pointer, Reference>::operator[](int n) const {
    return *(mPointer + n);
}


template<class T, class Pointer, class Reference>
iterator<T, Pointer, Reference> &iterator<T, Pointer, Reference>::operator+=(int n) {
    mPointer += n;
    return *this;
}


template<class T, class Pointer, class Reference>
iterator<T, Pointer, Reference> &iterator<T, Pointer, Reference>::operator-=(int n) {
    mPointer += n;
    return *this;
}


#endif //ARDUI_ITERATOR_H
