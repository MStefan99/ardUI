//
// Created by MStefan99 on 31.5.21.
//

#ifndef ARDUI_OBSERVER_H
#define ARDUI_OBSERVER_H

#include "platform.h"
#include LIST_H
#include "Observable.h"


template <class T>
class Observer final {
public:
	~Observer();

	void attachTo(Observable<T>* observable);
	void detachFrom(Observable<T>* observable);

	void (* onUpdate)(const T& newData) const {nullptr};

protected:
	LIST<Observable<T>> _observables {};
};


template <class T>
Observer<T>::~Observer<T>() {
	for (auto o : _observables) {
		detachFrom(o);
	}
}


template <class T>
void Observer<T>::attachTo(Observable<T>* observable) {
	_observables.push_back(observable);
	observable->attach(this);
}


template <class T>
void Observer<T>::detachFrom(Observable<T>* observable) {
	_observables.remove(observable);
	observable->detach(this);
}


#endif //ARDUI_OBSERVER_H
