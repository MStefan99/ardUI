//
// Created by MStefan99 on 25.11.19.
//

#ifndef ARDUI_LIST_H
#define ARDUI_LIST_H

#include "iterator.h"


namespace tl {
	template <class T>
	class list {
	protected:
		struct element;

	public:
		class iterator final {  // bidirectional iterator
		public:
			typedef _internal::bidirectional_iterator_tag iterator_category;

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

			friend class list;

		private:
			explicit iterator(element* elementPointer);
			element* _elementPointer {nullptr};
			element* _lastPointer {nullptr};
		};

		list() = default;
		list(const list& list);
		~list();

		void push_back(const T& value);
		void push_front(const T& value);

		T& front() const;
		T& back() const;

		void pop_back();
		void pop_front();

		unsigned int remove(const T& value);
		unsigned int remove_if(bool (* predicate)(const T&));

		iterator insert(iterator position, const T& value);

		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);
		void clear();

		unsigned int size() const;
		bool empty() const;

		list& operator=(const list& list);

		iterator begin() const;
		iterator end() const;

	protected:
		struct element {
			explicit element(const T& value, element* prev, element* next);
			element(const element& listElement) = default;
			~element() = default;

			T elementValue;
			element* prevElement {nullptr};
			element* nextElement {nullptr};
		};

		element* _first {nullptr};
		element* _last {nullptr};

		void destroyElement(element* e);
		unsigned int _listSize {0};
	};


	template <class T>
	list<T>::element::element(const T& value, element* prev, element* next):
			elementValue(value), prevElement(prev), nextElement(next) {
		// Nothing to do
	}


	template <class T>
	list<T>::list(const list& l) {
		for (auto e {l._first}; e != nullptr; e = e->nextElement) {
			push_back(e->elementValue);
		}
		_listSize = l.size();
	}


	template <class T>
	list<T>::~list() {
		clear();
	}


	template <class T>
	void list<T>::push_back(const T& value) {
		auto e = new element {value, _last, nullptr};

		if (!_first) {
			_first = e;
		}
		if (_last) {
			_last->nextElement = e;
		}
		_last = e;
		++_listSize;
	}


	template <class T>
	void list<T>::push_front(const T& value) {
		auto e = new element {value, nullptr, _first};

		if (!_last) {
			_last = e;
		}
		if (_first) {
			_first->prevElement = e;
		}
		_first = e;
		++_listSize;
	}


	template <class T>
	void list<T>::pop_back() {
		auto e {_last};
		if (e) {
			if (e->prevElement) {
				e->prevElement->nextElement = nullptr;
			} else {
				_first = nullptr;
			}

			_last = e->prevElement;
			--_listSize;
			delete e;
		}
	}


	template <class T>
	void list<T>::pop_front() {
		auto e {_first};
		if (e) {
			if (e->nextElement) {
				e->nextElement->prevElement = nullptr;
			} else {
				_last = nullptr;
			}

			_first = e->nextElement;
			--_listSize;
			delete e;
		}
	}


	template <class T>
	T& list<T>::front() const {
		return _first->elementValue;
	}


	template <class T>
	T& list<T>::back() const {
		return _last->elementValue;
	}


	template <class T>
	void list<T>::destroyElement(list<T>::element* e) {
		if (e->nextElement) {
			e->nextElement->prevElement = e->prevElement;
		} else {
			_last = e->prevElement;
		}
		if (e->prevElement) {
			e->prevElement->nextElement = e->nextElement;
		} else {
			_first = e->nextElement;
		}
		delete e;
	}


	template <class T>
	typename list<T>::iterator list<T>::insert(iterator position, const T& value) {
		auto e {position._elementPointer};
		auto n = new element {value, nullptr, e};

		if (e) {
			if (e->prevElement) {
				n->prevElement = e->prevElement;
				e->prevElement->nextElement = n;
			} else {
				_first = n;
			}
			e->prevElement = n;
		} else {
			if (!_first) {
				_first = n;
			}
			if (_last) {
				_last->nextElement = n;
				n->prevElement = _last;
			}
			_last = n;
		}
		++_listSize;
		return iterator(n);
	}


	template <class T>
	typename list<T>::iterator list<T>::erase(iterator position) {
		auto temp = position;

		++position;
		destroyElement(temp._elementPointer);
		--_listSize;
		return position;
	}


	template <class T>
	typename list<T>::iterator list<T>::erase(iterator f, iterator l) {
		while (f != l) {
			auto temp {f};
			++f;
			destroyElement(temp._elementPointer);
			--_listSize;
		}
		return l;
	}


	template <class T>
	unsigned int list<T>::remove(const T& value) {
		unsigned int i {0};
		element* e {_first};

		while (e) {
			auto temp = e;
			e = e->nextElement;
			if (temp->elementValue == value) {
				destroyElement(temp);
				++i;
				--_listSize;
			}
		}
		return i;
	}


	template <class T>
	unsigned int list<T>::remove_if(bool (* p)(const T&)) {
		unsigned int i {0};
		element* e {_first};

		while (e) {
			auto temp = e;
			e = e->nextElement;
			if (p(temp->elementValue)) {
				destroyElement(temp);
				++i;
				--_listSize;
			}
		}
		return i;
	}


	template <class T>
	void list<T>::clear() {
		element* e {_first};

		while (e) {
			auto temp = e;
			e = e->nextElement;
			destroyElement(temp);
			_listSize = 0;
		}
	}


	template <class T>
	unsigned int list<T>::size() const {
		return _listSize;
	}


	template <class T>
	bool list<T>::empty() const {
		return _first == nullptr;
	}


	template <class T>
	typename list<T>::iterator list<T>::begin() const {
		return iterator(_first);
	}


	template <class T>
	typename list<T>::iterator list<T>::end() const {
		iterator it {};
		it._lastPointer = _last;
		return it;
	}


	template <class T>
	list<T>& list<T>::operator=(const list& l) {
		if (this != &l) {
			clear();
			for (auto p = l._first; p != nullptr; p = p->nextElement) {
				push_back(p->elementValue);
			}
		}
		return *this;
	}


	template <class T>
	list<T>::iterator::iterator(element* elementPointer): _elementPointer(elementPointer) {}


	template <class T>
	typename list<T>::iterator& list<T>::iterator::operator++() {
		if (!_elementPointer->nextElement) {
			_lastPointer = _elementPointer;
		}
		_elementPointer = _elementPointer->nextElement;
		return *this;
	}


	template <class T>
	const typename list<T>::iterator list<T>::iterator::operator++(int) { // NOLINT(readability-const-return-type)
		iterator temp {*this};
		operator++();
		return temp;
	}


	template <class T>
	typename list<T>::iterator& list<T>::iterator::operator--() {
		if (!_elementPointer) {
			_elementPointer = _lastPointer;
		} else {
			_elementPointer = _elementPointer->prevElement;
		}
		return *this;
	}


	template <class T>
	const typename list<T>::iterator list<T>::iterator::operator--(int) { // NOLINT(readability-const-return-type)
		iterator temp {*this};
		operator--();
		return temp;
	}


	template <class T>
	bool list<T>::iterator::operator==(const iterator& it) const {
		return _elementPointer == it._elementPointer;
	}


	template <class T>
	bool list<T>::iterator::operator!=(const iterator& it) const {
		return _elementPointer != it._elementPointer;
	}


	template <class T>
	typename list<T>::iterator& list<T>::iterator::operator=(const T& value) {
		_elementPointer->elementValue = value;
		return *this;
	}


	template <class T>
	T* list<T>::iterator::operator->() const {
		return &_elementPointer->elementValue;
	}


	template <class T>
	T& list<T>::iterator::operator*() const {
		return _elementPointer->elementValue;
	}
}

#endif //ARDUI_LIST_H
