//
// Created by MStefan99 on 21.1.2020.
//

#ifndef ARDUI_VECTOR_H
#define ARDUI_VECTOR_H

#include "allocator.hpp"
#include "iterator.h"


// TODO: change size type


namespace tl {
	template <class T, class Alloc = allocator<T>>
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


	template <class T, class Alloc>
	vector<T, Alloc>::vector(const vector& v):
			_vectorSize(v._vectorSize), _vectorCapacity(v._vectorCapacity) {
		_vectorArray = Alloc().allocate(_vectorSize);
		for (unsigned int i {0}; i < v._vectorSize; ++i) {
			_vectorArray[i] = v._vectorArray[i];
		}
	}


	template <class T, class Alloc>
	vector<T, Alloc>::~vector() {
		for (unsigned int i {0}; i < _vectorSize; ++i) {
			Alloc().destroy(_vectorArray + i);
		}
		Alloc().deallocate(_vectorArray);
	}


	template <class T, class Alloc>
	void vector<T, Alloc>::push_back(const T& value) {
		if (_vectorSize == _vectorCapacity) {
			reserve(_vectorCapacity * 3 / 2 + 1);
		}

		_vectorArray[_vectorSize++] = value;
	}


	template <class T, class Alloc>
	void vector<T, Alloc>::pop_back() {
		--_vectorSize;
	}


	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(iterator position, const T& value) {
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


	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(vector<T, Alloc>::iterator position) {
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


	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator first, iterator last) {
		long i {first._elementPointer - _vectorArray};
		long n {last._elementPointer - first._elementPointer};

		while (i < _vectorSize - n) {
			_vectorArray[i] = _vectorArray[i + n];
			++i;
		}

		_vectorSize -= n;
		return last - n;
	}


	template <class T, class Alloc>
	void vector<T, Alloc>::clear() {
		for (unsigned int i {0}; i < _vectorSize; ++i) {
			_vectorArray[i] = T {};
		}
		_vectorSize = 0;
	}


	template <class T, class Alloc>
	void vector<T, Alloc>::resize(unsigned int n) {
		if (n > _vectorSize) {
			if (n > _vectorCapacity) {
				reserve(n);
			}
			for (unsigned int i {_vectorSize + 1}; i < n; ++i) {
				Alloc().construct(_vectorArray + i);
			}

		} else if (n < _vectorSize) {
			for (unsigned int i {n + 1}; i < _vectorSize; ++i) {
				Alloc().destroy(_vectorArray + i);
			}
		}
		_vectorSize = n;
	}


	template <class T, class Alloc>
	void vector<T, Alloc>::reserve(unsigned int n) {
		if (n <= _vectorCapacity) {
			_vectorCapacity = n;
			return;
		}

		T* temp = Alloc().allocate(n);
		for (unsigned int i {0}; i < _vectorSize; ++i) {
			temp[i] = _vectorArray[i];
			Alloc().destroy(_vectorArray + i);
		}
		for (unsigned int i {_vectorSize}; i < n; ++i) {
			Alloc().construct(temp + i);
		}

		Alloc().deallocate(_vectorArray);
		_vectorArray = temp;
		_vectorCapacity = n;
	}


	template <class T, class Alloc>
	T& vector<T, Alloc>::operator[](unsigned int n) const {
		return _vectorArray[n];
	}


	template <class T, class Alloc>
	vector<T, Alloc>& vector<T, Alloc>::operator=(const vector <T, Alloc>& vector) {
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


	template <class T, class Alloc>
	bool vector<T, Alloc>::empty() const {
		return _vectorSize == 0;
	}


	template <class T, class Alloc>
	unsigned int vector<T, Alloc>::size() const {
		return _vectorSize;
	}


	template <class T, class Alloc>
	unsigned int vector<T, Alloc>::capacity() const {
		return _vectorCapacity;
	}


	template <class T, class Alloc>
	T* vector<T, Alloc>::data() {
		return _vectorArray;
	}


	template <class T, class Alloc>
	const T* vector<T, Alloc>::data() const {
		return _vectorArray;
	}


	template <class T, class Alloc>
	T& vector<T, Alloc>::front() {
		return _vectorArray[0];
	}


	template <class T, class Alloc>
	T& vector<T, Alloc>::back() {
		return _vectorArray[_vectorSize - 1];
	}


	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::begin() const {
		return iterator(_vectorArray);
	}


	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::end() const {
		return iterator(_vectorArray + _vectorSize);
	}


	template <class T, class Alloc>
	vector<T, Alloc>::iterator::iterator(T* elementPointer): _elementPointer(elementPointer) {
	}


	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator& vector<T, Alloc>::iterator::operator++() {
		++_elementPointer;
		return *this;
	}


	template <class T, class Alloc>
	const typename vector<T, Alloc>::iterator
	vector<T, Alloc>::iterator::operator++(int) { // NOLINT(readability-const-return-type)
		iterator temp {*this};
		++_elementPointer;
		return temp;
	}


	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator& vector<T, Alloc>::iterator::operator--() {
		--_elementPointer;
		return *this;
	}


	template <class T, class Alloc>
	const typename vector<T, Alloc>::iterator
	vector<T, Alloc>::iterator::operator--(int) { // NOLINT(readability-const-return-type)
		iterator temp {*this};
		--_elementPointer;
		return temp;
	}


	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::iterator::operator+(int n) const {
		iterator temp {*this};
		temp._elementPointer += n;
		return temp;
	}


	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::iterator::operator-(int n) const {
		iterator temp {*this};
		temp._elementPointer -= n;
		return temp;
	}


	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator& vector<T, Alloc>::iterator::operator+=(int n) {
		_elementPointer += n;
		return *this;
	}


	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator& vector<T, Alloc>::iterator::operator-=(int n) {
		_elementPointer -= n;
		return *this;
	}


	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator& vector<T, Alloc>::iterator::operator=(const T& value) {
		*_elementPointer = value;
		return *this;
	}


	template <class T, class Alloc>
	T* vector<T, Alloc>::iterator::operator->() const {
		return _elementPointer;
	}


	template <class T, class Alloc>
	T& vector<T, Alloc>::iterator::operator*() const {
		return *_elementPointer;
	}


	template <class T, class Alloc>
	T& vector<T, Alloc>::iterator::operator[](unsigned int n) const {
		return _elementPointer[n];
	}


	template <class T, class Alloc>
	bool vector<T, Alloc>::iterator::operator==(const iterator& it) const {
		return _elementPointer == it._elementPointer;
	}


	template <class T, class Alloc>
	bool vector<T, Alloc>::iterator::operator!=(const iterator& it) const {
		return _elementPointer != it._elementPointer;
	}


	template <class T, class Alloc>
	bool vector<T, Alloc>::iterator::operator<(const iterator& it) const {
		return _elementPointer < it._elementPointer;
	}


	template <class T, class Alloc>
	bool vector<T, Alloc>::iterator::operator<=(const iterator& it) const {
		return _elementPointer <= it._elementPointer;
	}


	template <class T, class Alloc>
	bool vector<T, Alloc>::iterator::operator>(const iterator& it) const {
		return _elementPointer > it._elementPointer;
	}


	template <class T, class Alloc>
	bool vector<T, Alloc>::iterator::operator>=(const iterator& it) const {
		return _elementPointer >= it._elementPointer;
	}
}

#endif //ARDUI_VECTOR_H
