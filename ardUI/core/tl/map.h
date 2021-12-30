//
// Created by MStefan99 on 29.1.20.
//

#ifndef ARDUI_MAP_H
#define ARDUI_MAP_H

#include "pair.h"
#include "less.h"
#include "iterator.h"


template <class pNode>
static pNode Leftmost(pNode pointer) {
	if (pointer) {
		while (pointer->left) {
			pointer = pointer->left;
		}
	}
	return pointer;
}


template <class pNode>
static pNode Rightmost(pNode pointer) {
	if (pointer) {
		while (pointer->right) {
			pointer = pointer->right;
		}
	}
	return pointer;
}


namespace tl {
	template <class Key, class T, class Comp = less<Key>>
	class map {
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

			pair<const Key, T>* operator->() const;
			pair<const Key, T>& operator*() const;

			friend class map;

		private:
			explicit iterator(element* currentElement, element* lastElement = nullptr);
			element* _currentElement {nullptr};
			element* _lastElement {nullptr};
		};

		map() = default;
		map(const map& m);
		~map();

		T& operator[](const Key& k);

		bool empty() const;
		unsigned int size() const;

		iterator find(const Key& k) const;

		pair<iterator, bool> insert(const pair<const Key, T>& value);

		iterator erase(iterator position);
		unsigned int erase(const Key& k);
		iterator erase(iterator first, iterator last);
		void clear();

		iterator begin() const;
		iterator end() const;

	protected:
		struct element {
			explicit element(const pair<const Key, T>& value, element* parent);
			explicit element(const Key& k, element* parent);

			pair<const Key, T> value;
			element* parent {nullptr};
			element* left {nullptr};
			element* right {nullptr};
		};

		void replaceElement(element* o, element* n);
		void destroyElement(element* e);
		element* findElement(const Key& k) const;

		element* _mapRoot {nullptr};
		Comp _less {};
		unsigned int _mapSize {0};
		bool _balancingLeft {true};
	};


	template <class Key, class T, class Comp>
	map<Key, T, Comp>::iterator::iterator(element* currentElement, element* lastElement):
			_currentElement(currentElement),
			_lastElement(lastElement) {
	}


	template <class Key, class T, class Comp>
	typename map<Key, T, Comp>::iterator& map<Key, T, Comp>::iterator::operator++() {
		if (_currentElement->right) {
			_currentElement = Leftmost(_currentElement->right);
			_lastElement = _currentElement;
		} else if (_currentElement->parent) {
			while (_currentElement->parent && _currentElement->parent->right == _currentElement) {
				_currentElement = _currentElement->parent;
			}
			if (_currentElement->parent) {
				_currentElement = _currentElement->parent;
			} else {
				_currentElement = nullptr;
			}
		} else {
			_lastElement = _currentElement;
			_currentElement = nullptr;
		}
		return *this;
	}


	template <class Key, class T, class Comp>
	const typename map<Key, T, Comp>::iterator  // NOLINT(readability-const-return-type)
	map<Key, T, Comp>::iterator::operator++(int) {
		auto temp {*this};
		operator++();
		return temp;
	}


	template <class Key, class T, class Comp>
	typename map<Key, T, Comp>::iterator& map<Key, T, Comp>::iterator::operator--() {
		if (!_currentElement) {
			_currentElement = _lastElement;
		} else if (_currentElement->left) {
			_currentElement = Rightmost(_currentElement->left);
		} else if (_currentElement->parent) {
			while (_currentElement->parent && _currentElement->parent->left == _currentElement) {
				_currentElement = _currentElement->parent;
			}
			if (_currentElement->parent) {
				_currentElement = _currentElement->parent;
			} else {
				_currentElement = nullptr;
			}
		} else {
			_lastElement = _currentElement;
			_currentElement = nullptr;
		}
		return *this;
	}


	template <class Key, class T, class Comp>
	const typename map<Key, T, Comp>::iterator  // NOLINT(readability-const-return-type)
	map<Key, T, Comp>::iterator::operator--(int) {
		auto temp {*this};
		operator--();
		return temp;
	}


	template <class Key, class T, class Comp>
	bool map<Key, T, Comp>::iterator::operator==(const iterator& it) const {
		return _currentElement == it._currentElement;
	}


	template <class Key, class T, class Comp>
	bool map<Key, T, Comp>::iterator::operator!=(const iterator& it) const {
		return _currentElement != it._currentElement;
	}


	template <class Key, class T, class Comp>
	typename map<Key, T, Comp>::iterator& map<Key, T, Comp>::iterator::operator=(const T& value) {
		_currentElement->value.second = value;
		return *this;
	}


	template <class Key, class T, class Comp>
	pair<const Key, T>* map<Key, T, Comp>::iterator::operator->() const {
		return &_currentElement->value;
	}


	template <class Key, class T, class Comp>
	pair<const Key, T>& map<Key, T, Comp>::iterator::operator*() const {
		return _currentElement->value;
	}


	template <class Key, class T, class Comp>
	map<Key, T, Comp>::element::element(const pair<const Key, T>& v, element* p):
			value(v),
			parent(p) {
		// Nothing to do
	}


	template <class Key, class T, class Comp>
	map<Key, T, Comp>::element::element(const Key& k, element* p):
			value(k, T {}),
			parent(p) {
	}


	template <class Key, class T, class Comp>
	bool map<Key, T, Comp>::empty() const {
		return !_mapRoot;
	}


	template <class Key, class T, class Comp>
	unsigned int map<Key, T, Comp>::size() const {
		return _mapSize;
	}


	template <class Key, class T, class Comp>
	typename map<Key, T, Comp>::iterator map<Key, T, Comp>::find(const Key& k) const {
		return iterator(findElement(k));
	}


	template <class Key, class T, class Comp>
	pair<typename map<Key, T, Comp>::iterator, bool> map<Key, T, Comp>::insert(const pair<const Key, T>& value) {
		element** node {&_mapRoot};
		element** parent {&_mapRoot};

		while (*node) {
			Key k = (*node)->value.first;
			if (k == value.first) {
				return {iterator(*node), false};
			} else if (_less(value.first, k)) {
				parent = node;
				node = &(*node)->left;
			} else {
				parent = node;
				node = &(*node)->right;
			}
		}
		++_mapSize;
		*node = new element {value, *parent};
		return {iterator(*node), true};
	}


	template <class Key, class T, class Comp>
	typename map<Key, T, Comp>::iterator map<Key, T, Comp>::erase(iterator position) {
		auto temp {position};
		++position;
		destroyElement(temp._currentElement);
		--_mapSize;

		return position;
	}


	template <class Key, class T, class Comp>
	unsigned int map<Key, T, Comp>::erase(const Key& k) {
		element* e {findElement(k)};

		if (e) {
			destroyElement(e);
			--_mapSize;
			return 1;
		} else {
			return 0;
		}
	}


	template <class Key, class T, class Comp>
	typename map<Key, T, Comp>::iterator map<Key, T, Comp>::erase(iterator first, iterator last) {
		element* node {first._currentElement};
		element* temp {node};
		bool deleteRoot {false};

		while (node != last._currentElement) {
			if (node == _mapRoot) {
				deleteRoot = true;
			}
			if (node->right) {
				node = Leftmost(node->right);
			} else if (node->parent) {
				while (node->parent && node->parent->right == node) {
					temp = node;
					node = node->parent;
					destroyElement(temp);
					--_mapSize;
				}
				temp = node;
				node = node->parent;
				destroyElement(temp);
				--_mapSize;
			}
		}
		if (deleteRoot && _mapRoot) {
			temp = _mapRoot;
			destroyElement(temp);
			--_mapSize;
		}
		return last;
	}


	template <class Key, class T, class Comp>
	void map<Key, T, Comp>::clear() {
		element* node {Leftmost(_mapRoot)};
		element* temp {node};

		while (node) {
			if (node->right) {
				node = Leftmost(node->right);
			} else if (node->parent) {
				while (node->parent && node->parent->right == node) {
					temp = node;
					node = node->parent;
					destroyElement(temp);
				}
				temp = node;
				node = node->parent;
				if (!temp->right) {
					destroyElement(temp);
				}
			} else if (node == _mapRoot && !node->right && !node->left) {
				destroyElement(node);
				node = nullptr;
			}
		}
		_mapSize = 0;
	}


	template <class Key, class T, class Comp>
	map<Key, T, Comp>::map(const map& m) {
		if (m._mapRoot) {
			_mapRoot = new element {{m._mapRoot->value}, nullptr};
			_mapSize = 1;

			auto e {m._mapRoot};
			while (e->left) {
				e = e->left;
				insert({e->value});
			}
			while (e != nullptr) {
				if (e->right) {
					e = e->right;
					insert({e->value});
					while (e->left) {
						e = e->left;
						insert({e->value});
					}
				} else if (e->parent) {
					while (e->parent && e->parent->right == e) {
						e = e->parent;
					}
					if (e->parent) {
						e = e->parent;
					} else {
						break;
					}
				} else {
					break;
				}
			}
		}
	}


	template <class Key, class T, class Comp>
	map<Key, T, Comp>::~map() {
		clear();
	}


	template <class Key, class T, class Comp>
	T& map<Key, T, Comp>::operator[](const Key& k) {
		element** node {&_mapRoot};
		element** parent {&_mapRoot};

		while (*node) {
			Key cKey = (*node)->value.first;
			if (cKey == k) {
				return (*node)->value.second;
			} else if (_less(k, cKey)) {
				parent = node;
				node = &(*node)->left;
			} else {
				parent = node;
				node = &(*node)->right;
			}
		}
		++_mapSize;
		*node = new element {k, *parent};
		return (*node)->value.second;
	}


	template <class Key, class T, class Comp>
	typename map<Key, T, Comp>::iterator map<Key, T, Comp>::begin() const {
		return map::iterator(Leftmost(_mapRoot));
	}


	template <class Key, class T, class Comp>
	typename map<Key, T, Comp>::iterator map<Key, T, Comp>::end() const {
		return map::iterator(nullptr, Rightmost(_mapRoot));
	}


	template <class Key, class T, class Comp>
	void map<Key, T, Comp>::replaceElement(element* o, element* n) {
		if (o->parent) {
			if (o == o->parent->left) {
				o->parent->left = n;
			} else {
				o->parent->right = n;
			}
		}
		if (o->right) {
			o->right->parent = n;
		}
		if (o->left) {
			o->left->parent = n;
		}
		n->parent = o->parent;
	}


	template <class Key, class T, class Comp>
	void map<Key, T, Comp>::destroyElement(element* e) {
		element* replacement {};

		if (e->left && e->right) {
			if (_balancingLeft) {
				replacement = Rightmost(e->left);
				replacement->right = e->right;
			} else {
				replacement = Leftmost(e->right);
				replacement->left = e->left;
			}
			_balancingLeft = !_balancingLeft;
			replaceElement(e, replacement);
		} else if (e->left) {
			replaceElement(e, e->left);
		} else if (e->right) {
			replaceElement(e, e->right);
		} else {
			if (e->parent) {  // check if tree root is being unlinked
				if (e->parent->left == e) {
					e->parent->left = nullptr;
				} else {
					e->parent->right = nullptr;
				}
			}
		}
		if (e == _mapRoot) {
			_mapRoot = replacement;
		}
		delete (e);
	}


	template <class Key, class T, class Comp>
	typename map<Key, T, Comp>::element* map<Key, T, Comp>::findElement(const Key& k) const {
		element* node {_mapRoot};

		while (node) {
			if (_less(k, node->value.first)) {
				node = node->left;
			} else if (_less(node->value.first, k)) {
				node = node->right;
			} else {
				return node;
			}
		}
		return nullptr;
	}
}

#endif //ARDUI_MAP_H
