//
// Created by MStefan99 on 29.1.20.
//

#ifndef ARDUI_LESS_H
#define ARDUI_LESS_H

namespace ardui {
	template <class T>
	struct less {
		bool operator()(const T& x, const T& y) const;

		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef bool result_type;
	};


	template <class T>
	bool ardui::less<T>::operator()(const T& x, const T& y) const {
		return x < y;
	}
}
#endif //ARDUI_LESS_H
