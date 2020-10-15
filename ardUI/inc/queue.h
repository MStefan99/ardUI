//
// Created by MStefan99 on 3.4.20.
//

#ifndef ARDUI_QUEUE_H
#define ARDUI_QUEUE_H


#include "list.h"


namespace ardui {
	template <class T, class Container = list <T>>
	class queue {
	public:
		queue() = default;
		~queue() = default;

		bool empty() const;
		int size() const;

		T& front() const;
		T& back() const;

		void pop();
		void push(const T& value);

	protected:
		Container c {};
	};


	template <class T, class Container>
	bool queue<T, Container>::empty() const {
		return c.empty();
	}


	template <class T, class Container>
	int queue<T, Container>::size() const {
		return c.size();
	}


	template <class T, class Container>
	T& queue<T, Container>::front() const {
		return c.front();
	}


	template <class T, class Container>
	T& queue<T, Container>::back() const {
		return c.back();
	}


	template <class T, class Container>
	void queue<T, Container>::pop() {
		c.pop_front();
	}


	template <class T, class Container>
	void queue<T, Container>::push(const T& value) {
		c.push_back(value);
	}
}

#endif //ARDUI_QUEUE_H
