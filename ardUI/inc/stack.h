//
// Created by MStefan99 on 4.2.20.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCInconsistentNamingInspection"
#ifndef ARDUI_STACK_H
#define ARDUI_STACK_H

namespace ardui {
	template <class T, class Container = list <T>>
	class stack {
	public:
		stack() = default;
		~stack() = default;

		bool empty() const;
		int size() const;

		T& top() const;

		void pop();
		void push(const T& value);

	protected:
		Container c {};
	};


	template <class T, class Container>
	bool stack<T, Container>::empty() const {
		return c.empty();
	}


	template <class T, class Container>
	int stack<T, Container>::size() const {
		return c.size();
	}


	template <class T, class Container>
	T& stack<T, Container>::top() const {
		return c.back();
	}


	template <class T, class Container>
	void stack<T, Container>::pop() {
		c.pop_back();
	}


	template <class T, class Container>
	void stack<T, Container>::push(const T& value) {
		c.push_back(value);
	}
}

#endif //ARDUI_STACK_H

#pragma clang diagnostic pop