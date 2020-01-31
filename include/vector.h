//
// Created by MStefan99 on 21.1.2020.
//

#ifndef ARDUI_TEST_VECTOR_H
#define ARDUI_TEST_VECTOR_H

namespace ardui {
    template <class T>
    class vector {
    public:
        class iterator {  // random access iterator
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

            iterator operator+(int n) const;
            iterator operator-(int n) const;

            iterator& operator+=(int n);
            iterator& operator-=(int n);

            bool operator<(const iterator& it) const;
            bool operator<=(const iterator& it) const;
            bool operator>(const iterator& it) const;
            bool operator>=(const iterator& it) const;

            T& operator[](int n) const;

            friend class vector;

        private:
            explicit iterator(T* elementPointer);
            T* elementPointer;
        };

        vector() = default;
        ~vector();

        void push_back(const T& value);
        void pop_back();

        iterator insert(iterator pos, const T& value);
        iterator erase(iterator position);
        iterator erase(iterator first, iterator last);
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
    void vector<T>::push_back(const T &value) {
        if (vectorSize == vectorCapacity) {
            resize(vectorCapacity * 1.1 + 1);
        }

        vectorArray[vectorSize] = value;
        ++vectorSize;
    }


    template<class T>
    void vector<T>::pop_back() {
        --vectorSize;
    }


    template <class T>
    typename vector<T>::iterator vector<T>::insert(iterator position, const T &value) {
        if (vectorSize == vectorCapacity) {
            resize(vectorCapacity * 1.1 + 1);
        }

        // TODO: rewrite using iterator
    }


    template <class T>
    typename vector<T>::iterator vector<T>::erase(vector<T>::iterator position) {
        while (position != end()) {
            *position = *position + 1;
        }
        return ++position;
    }


    template <class T>
    typename vector<T>::iterator vector<T>::erase(iterator first, iterator last) {
        while (first != last) {
            *first = *first + 1;
        }
        return last;
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


    template <class T>
    vector<T>& vector<T>::operator=(const vector<T> &vector) {
        if (this != &vector) {
            resize(vector.vectorSize);
            for (int i {0}; i < vectorSize; ++i) {
                vectorArray[i] = vector.vectorArray[i];
            }
        } else {
            return *this;
        }
    }


    template<class T>
    int vector<T>::size() const {
        return vectorSize;
    }


    template<class T>
    int vector<T>::capacity() const {
        return vectorCapacity;
    }


    template <class T>
    typename vector<T>::iterator vector<T>::begin() const {
        return iterator(vectorArray);
    }


    template <class T>
    typename vector<T>::iterator vector<T>::end() const {
        return iterator(vectorArray + vectorSize);
    }


    template <class T>
    vector<T>::iterator::iterator(T *elementPointer): elementPointer(elementPointer) {
    }


    template <class T>
    typename vector<T>::iterator& vector<T>::iterator::operator++() {
        ++elementPointer;
        return *this;
    }


    template <class T>
    const typename vector<T>::iterator vector<T>::iterator::operator++(int) { // NOLINT(readability-const-return-type)
        iterator temp {*this};
        ++elementPointer;
        return temp;
    }


    template <class T>
    typename vector<T>::iterator& vector<T>::iterator::operator--() {
        --elementPointer;
        return *this;
    }


    template <class T>
    const typename vector<T>::iterator vector<T>::iterator::operator--(int) { // NOLINT(readability-const-return-type)
        iterator temp {*this};
        --elementPointer;
        return temp;
    }


    template <class T>
    typename vector<T>::iterator vector<T>::iterator::operator+(int n) const {
        iterator temp {*this};
        temp.elementPointer += n;
        return temp;
    }


    template <class T>
    typename vector<T>::iterator vector<T>::iterator::operator-(int n) const {
        iterator temp {*this};
        temp.elementPointer -= n;
        return temp;
    }


    template <class T>
    typename vector<T>::iterator& vector<T>::iterator::operator+=(int n) {
        elementPointer += n;
        return *this;
    }


    template <class T>
    typename vector<T>::iterator& vector<T>::iterator::operator-=(int n) {
        elementPointer -= n;
        return *this;
    }


    template <class T>
    typename vector<T>::iterator& vector<T>::iterator::operator=(const T &value) {
        *elementPointer = value;
    }


    template <class T>
    T* vector<T>::iterator::operator->() const {
        return elementPointer;
    }


    template <class T>
    T& vector<T>::iterator::operator*() const {
        return *elementPointer;
    }


    template <class T>
    T& vector<T>::iterator::operator[](int n) const {
        return elementPointer[n];
    }


    template <class T>
    bool vector<T>::iterator::operator==(const iterator &it) const {
        return elementPointer == it.elementPointer;
    }


    template <class T>
    bool vector<T>::iterator::operator!=(const iterator &it) const {
        return elementPointer != it.elementPointer;
    }


    template <class T>
    bool vector<T>::iterator::operator<(const iterator &it) const {
        return elementPointer < it.elementPointer;
    }


    template <class T>
    bool vector<T>::iterator::operator<=(const iterator &it) const {
        return elementPointer <= it.elementPointer;
    }


    template <class T>
    bool vector<T>::iterator::operator>(const iterator &it) const {
        return elementPointer > it.elementPointer;
    }


    template <class T>
    bool vector<T>::iterator::operator>=(const iterator &it) const {
        return elementPointer >= it.elementPointer;
    }
}


#endif //ARDUI_TEST_VECTOR_H
