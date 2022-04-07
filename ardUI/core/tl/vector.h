//
// Created by MStefan99 on 21.1.2020.
//

#ifndef ARDUI_VECTOR_H
#define ARDUI_VECTOR_H

#include "iterator.h"


// TODO: change size type


namespace tl {
	template <class T>
	class vector {
	public:
		class iterator final {  // random access iterator
		public:
			typedef _internal::random_access_iterator_tag iterator_category;

			iterator() = default;

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

			T& operator[](unsigned int n) const;

			friend class vector;

		private:
			explicit iterator(T* elementPointer);
			T* _elementPointer {nullptr};
		};

		vector() = default;
		vector(const vector& v);
		~vector();

		void push_back(const T& value);
		void pop_back();

		iterator insert(iterator pos, const T& value);
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);
		void clear();

		T& operator[](unsigned int n) const;
		vector& operator=(const vector& vector);

		bool empty() const;
		unsigned int size() const;
		unsigned int capacity() const;

		T* data();
		const T* data() const;

		void resize(unsigned int n);
		void reserve(unsigned int n);

		T& front();
		T& back();

		iterator begin() const;
		iterator end() const;

	protected:
		T* _vectorArray {nullptr};
		unsigned int _vectorSize {0};
		unsigned int _vectorCapacity {0};
	};


	template <class T>
	vector<T>::vector(const vector& v):
			_vectorSize(v._vectorSize), _vectorCapacity(v._vectorCapacity) {
		_vectorArray = new T[_vectorSize];
		for (unsigned int i {0}; i < v._vectorSize; ++i) {
			_vectorArray[i] = v._vectorArray[i];
		}
	}


	template <class T>
	vector<T>::~vector() {
		delete[] _vectorArray;
	}


	template <class T>
	void vector<T>::push_back(const T& value) {
		if (_vectorSize == _vectorCapacity) {
			reserve(_vectorCapacity * 3 / 2 + 1);
		}

		_vectorArray[_vectorSize++] = value;
	}


	template <class T>
	void vector<T>::pop_back() {
		--_vectorSize;
	}


	template <class T>
	typename vector<T>::iterator vector<T>::insert(iterator position, const T& value) {
		auto i {position._elementPointer - _vectorArray};

		if (_vectorSize == _vectorCapacity) {
			reserve(_vectorCapacity * 3 / 2 + 1);
		}
		for (auto j {_vectorSize}; j > i; --j) {
			_vectorArray[j] = _vectorArray[j - 1];
		}
		_vectorArray[i] = value;
		++_vectorSize;

		return position;
	}


	template <class T>
	typename vector<T>::iterator vector<T>::erase(vector<T>::iterator position) {
		auto i {position._elementPointer - _vectorArray};

		if (i > _vectorSize - 1) {
			return position;
		}
		while (i < _vectorSize - 1) {
			_vectorArray[i] = _vectorArray[i + 1];
			++i;
		}
		--_vectorSize;
		return position;
	}


	template <class T>
	typename vector<T>::iterator vector<T>::erase(iterator first, iterator last) {
		long i {first._elementPointer - _vectorArray};
		long n {last._elementPointer - first._elementPointer};

		while (i < _vectorSize - n) {
			_vectorArray[i] = _vectorArray[i + n];
			++i;
		}

		_vectorSize -= n;
		return last - n;
	}


	template <class T>
	void vector<T>::clear() {
		for (unsigned int i {0}; i < _vectorSize; ++i) {
			_vectorArray[i] = T {};
		}
		_vectorSize = 0;
	}


	template <class T>
	void vector<T>::resize(unsigned int n) {
		if (n <= _vectorSize) {
			_vectorSize = n;
			return;
		}

		_vectorSize = n;
		T* temp = new T[n];

		if (_vectorArray) {
			for (unsigned int i {0}; i < _vectorSize && i < n; ++i) {
				temp[i] = _vectorArray[i];
			}
			delete[] _vectorArray;
		}
		_vectorArray = temp;
	}


	template <class T>
	void vector<T>::reserve(unsigned int n) {
		if (n <= _vectorCapacity) {
			_vectorCapacity = n;
			return;
		}

		_vectorCapacity = n;

		T* temp = new T[n];
		if (_vectorArray) {
			for (unsigned int i {0}; i < _vectorSize && i < n; ++i) {
				temp[i] = _vectorArray[i];
			}
			delete[] _vectorArray;
		}
		_vectorArray = temp;
	}


	template <class T>
	T& vector<T>::operator[](unsigned int n) const {
		return _vectorArray[n];
	}


	template <class T>
	vector<T>& vector<T>::operator=(const vector <T>& vector) {
		if (this != &vector) {
			resize(vector._vectorSize);
			for (unsigned int i {0}; i < vector.size(); ++i) {
				_vectorArray[i] = vector._vectorArray[i];
			}
			_vectorSize = vector.size();
			_vectorCapacity = vector.capacity();
		}
		return *this;
	}


	template <class T>
	bool vector<T>::empty() const {
		return _vectorSize == 0;
	}


	template <class T>
	unsigned int vector<T>::size() const {
		return _vectorSize;
	}


	template <class T>
	unsigned int vector<T>::capacity() const {
		return _vectorCapacity;
	}


	template <class T>
	T* vector<T>::data() {
		return _vectorArray;
	}


	template <class T>
	const T* vector<T>::data() const {
		return _vectorArray;
	}


	template <class T>
	T& vector<T>::front() {
		return _vectorArray[0];
	}


	template <class T>
	T& vector<T>::back() {
		return _vectorArray[_vectorSize - 1];
	}


	template <class T>
	typename vector<T>::iterator vector<T>::begin() const {
		return iterator(_vectorArray);
	}


	template <class T>
	typename vector<T>::iterator vector<T>::end() const {
		return iterator(_vectorArray + _vectorSize);
	}


	template <class T>
	vector<T>::iterator::iterator(T* elementPointer): _elementPointer(elementPointer) {
	}


	template <class T>
	typename vector<T>::iterator& vector<T>::iterator::operator++() {
		++_elementPointer;
		return *this;
	}


	template <class T>
	const typename vector<T>::iterator vector<T>::iterator::operator++(int) { // NOLINT(readability-const-return-type)
		iterator temp {*this};
		++_elementPointer;
		return temp;
	}


	template <class T>
	typename vector<T>::iterator& vector<T>::iterator::operator--() {
		--_elementPointer;
		return *this;
	}


	template <class T>
	const typename vector<T>::iterator vector<T>::iterator::operator--(int) { // NOLINT(readability-const-return-type)
		iterator temp {*this};
		--_elementPointer;
		return temp;
	}


	template <class T>
	typename vector<T>::iterator vector<T>::iterator::operator+(int n) const {
		iterator temp {*this};
		temp._elementPointer += n;
		return temp;
	}


	template <class T>
	typename vector<T>::iterator vector<T>::iterator::operator-(int n) const {
		iterator temp {*this};
		temp._elementPointer -= n;
		return temp;
	}


	template <class T>
	typename vector<T>::iterator& vector<T>::iterator::operator+=(int n) {
		_elementPointer += n;
		return *this;
	}


	template <class T>
	typename vector<T>::iterator& vector<T>::iterator::operator-=(int n) {
		_elementPointer -= n;
		return *this;
	}


	template <class T>
	typename vector<T>::iterator& vector<T>::iterator::operator=(const T& value) {
		*_elementPointer = value;
		return *this;
	}


	template <class T>
	T* vector<T>::iterator::operator->() const {
		return _elementPointer;
	}


	template <class T>
	T& vector<T>::iterator::operator*() const {
		return *_elementPointer;
	}


	template <class T>
	T& vector<T>::iterator::operator[](unsigned int n) const {
		return _elementPointer[n];
	}


	template <class T>
	bool vector<T>::iterator::operator==(const iterator& it) const {
		return _elementPointer == it._elementPointer;
	}


	template <class T>
	bool vector<T>::iterator::operator!=(const iterator& it) const {
		return _elementPointer != it._elementPointer;
	}


	template <class T>
	bool vector<T>::iterator::operator<(const iterator& it) const {
		return _elementPointer < it._elementPointer;
	}


	template <class T>
	bool vector<T>::iterator::operator<=(const iterator& it) const {
		return _elementPointer <= it._elementPointer;
	}


	template <class T>
	bool vector<T>::iterator::operator>(const iterator& it) const {
		return _elementPointer > it._elementPointer;
	}


	template <class T>
	bool vector<T>::iterator::operator>=(const iterator& it) const {
		return _elementPointer >= it._elementPointer;
	}
}

#endif //ARDUI_VECTOR_H
