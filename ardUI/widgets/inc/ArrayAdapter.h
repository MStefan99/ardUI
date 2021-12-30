//
// Created by MStefan99 on 31.5.21.
//

#ifndef ARDUI_ARRAYADAPTER_H
#define ARDUI_ARRAYADAPTER_H

#include "platform.h"
#include LIST_H

#include "Adapter.h"


template <class T>
class ArrayAdapter: public Adapter<T> {
public:
	ArrayAdapter() = default;
	explicit ArrayAdapter(T data[], int length);
	explicit ArrayAdapter(TL_NS::list<T> list);

	const T& getItem(int position) const override;
	int getCount() const override;
	bool isEmpty() const override;

	TL_NS::list<T> list;
};


template <class T>
ArrayAdapter<T>::ArrayAdapter(T data[], int length) {
	for (int i {0}; i < length; ++i) {
		list.push_back(data[i]);
	}
	// Nothing to do
}


template <class T>
ArrayAdapter<T>::ArrayAdapter(TL_NS::list<T> list): list {list} {
	// Nothing to do
}


template <class T>
const T& ArrayAdapter<T>::getItem(int position) const {
	auto it = list.begin();
	for (int i {0}; i < position; ++i) {
		++it;
	}
	return *it;
}


template <class T>
int ArrayAdapter<T>::getCount() const {
	return list.size();
}


template <class T>
bool ArrayAdapter<T>::isEmpty() const {
	return false;
}


#endif //ARDUI_ARRAYADAPTER_H
