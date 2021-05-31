//
// Created by MStefan99 on 31.5.21.
//

#ifndef ARDUI_ARRAYADAPTER_H
#define ARDUI_ARRAYADAPTER_H

#include "Adapter.h"



template <class T>
class ArrayAdapter: public Adapter<T> {
public:
	ArrayAdapter() = default;
	explicit ArrayAdapter(T data[]);
	explicit ArrayAdapter(LIST<T> list);

	int getCount() const override;
	bool isEmpty() const override;
	void notifyDataSetChanged() const override;

protected:
	LIST<T> _list;
};


template <class T>
ArrayAdapter<T>::ArrayAdapter(T data[]): _list {data} {
	// Nothing to do
}


template <class T>
ArrayAdapter<T>::ArrayAdapter(LIST<T> list): _list{list} {
	// Nothing to do
}


template <class T>
int ArrayAdapter<T>::getCount() const {
	return _list.size();
}


template <class T>
bool ArrayAdapter<T>::isEmpty() const {
	return false;
}


template <class T>
void ArrayAdapter<T>::notifyDataSetChanged() const {
	Observable<T>::update();
}


#endif //ARDUI_ARRAYADAPTER_H
