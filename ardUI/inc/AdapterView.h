//
// Created by MStefan99 on 31.5.21.
//

#ifndef ARDUI_ADAPTERVIEW_H
#define ARDUI_ADAPTERVIEW_H

#include "Adapter.h"
#include "ViewGroup.h"


template <class T>
class AdapterView: public ViewGroup {
public:
	AdapterView() = default;
	explicit AdapterView(const Adapter<T>& adapter);

	void setAdapter(Adapter<T>* adapter);
	Adapter<T>* getAdapter() const;

protected:
	Adapter<T>* _adapter {nullptr};
};


template <class T>
AdapterView<T>::AdapterView(const Adapter<T>& adapter): _adapter {&adapter} {
}


template <class T>
void AdapterView<T>::setAdapter(Adapter<T>* adapter) {
	_adapter = adapter;
}


template <class T>
Adapter<T>* AdapterView<T>::getAdapter() const {
	return _adapter;
}


#endif //ARDUI_ADAPTERVIEW_H
