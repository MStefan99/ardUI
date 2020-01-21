//
// Created by MStefan99 on 21.1.2020.
//

#ifndef ARDUI_TEST_VECTOR_H
#define ARDUI_TEST_VECTOR_H


template <class T>
class vector {
public:
    class iterator {  // random access iterator

    };

    vector() = default;
    ~vector();

    void push_back(const T& content);
    void pop_back();

    void insert(int pos, const T& content);
    void erase(iterator position);
    void erase(iterator first, iterator last);
    void clear();
    
    T& operator[](int n) const;
    vector& operator=(const vector& vector);
    
    int size() const;
    int capacity() const;

    void resize(int n);

    iterator begin() const;
    iterator end() const;

protected:
    T* vectorArray {nullptr};
    int vectorSize {0};
    int vectorCapacity {0};
};


template <class T>
vector<T>::~vector() {
    delete[] vectorArray;
}


template <class T>
void vector<T>::push_back(const T &content) {
    if (vectorSize == vectorCapacity) {
        resize(vectorCapacity * 1.1 + 1);
    }

    vectorArray[vectorSize] = content;
    ++vectorSize;
}


template<class T>
void vector<T>::pop_back() {
    --vectorSize;
}


template <class T>
void vector<T>::insert(int pos, const T &content) {
    if (vectorSize == vectorCapacity) {
        resize(vectorCapacity * 1.1 + 1);
    }

    for (int i {pos}; i < vectorSize; ++i) {
        vectorArray[i + 1] = vectorArray[i];
    }

    vectorArray[pos] = content;
    ++vectorSize;
}


template <class T>
void vector<T>::erase(vector<T>::iterator position) {
    while (position != end()) {
        *position = *position + 1;
    }
}


template <class T>
void vector<T>::erase(iterator first, iterator last) {
    while (first != last) {
        *first = *first + 1;
    }
}


template <class T>
void vector<T>::clear() {
    for (int i {0}; i < vectorSize; ++i) {
        vectorArray[i] = T{};
    }
    vectorSize = 0;
}


template <class T>
void vector<T>::resize(int n) {
    T* temp = new T[n];
    vectorCapacity = n;

    if (vectorArray) {
        for (int i {0}; i < vectorSize && i < n; ++i) {
            temp[i] = vectorArray[i];
        }
        delete[] vectorArray;
    }
    vectorArray = temp;
}


template<class T>
T &vector<T>::operator[](int n) const {
    return vectorArray[n];
}


template<class T>
int vector<T>::size() const {
    return vectorSize;
}


template<class T>
int vector<T>::capacity() const {
    return vectorCapacity;
}


#endif //ARDUI_TEST_VECTOR_H
