//
// Created by MStefan99 on 31.5.21.
//

#ifndef ARDUI_ADAPTERVIEW_H
#define ARDUI_ADAPTERVIEW_H

#include "Adapter.h"
#include "ViewGroup.h"
#include "Observer.h"


template <class T>
class AdapterView: public ViewGroup {
public:
	AdapterView() = default;

	void setAdapter(Adapter<T>* adapter);
	Adapter<T>* getAdapter() const;

protected:
	Adapter<T>* _adapter {nullptr};
	Observer<T> _observer {};
};


template <class T>
void AdapterView<T>::setAdapter(Adapter<T>* adapter) {
	if (_adapter) {
		_observer.detachFrom(adapter);
	}
	_adapter = adapter;
	_observer.attachTo(adapter);
}


template <class T>
Adapter<T>* AdapterView<T>::getAdapter() const {
	return _adapter;
}

#endif //ARDUI_ADAPTERVIEW_H
