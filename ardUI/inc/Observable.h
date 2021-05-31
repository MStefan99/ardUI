//
// Created by MStefan99 on 31.5.21.
//

#ifndef ARDUI_OBSERVABLE_H
#define ARDUI_OBSERVABLE_H

#include "platform.h"
#include LIST_H


template <class T>
class Observer;


template <class T>
class Observable final {
public:
	~Observable();

	void attach(Observer<T>* observer);
	void detach(Observer<T>* observer);

	void update(const T& newData) const;

protected:
	LIST<Observer<T>> _observers {};
};


template <class T>
Observable<T>::~Observable<T>() {
	for (auto o : _observers) {
		o->detach(this);
	}
}


template <class T>
void Observable<T>::attach(Observer<T>* observer) {
	_observers.push_back(observer);
}


template <class T>
void Observable<T>::detach(Observer<T>* observer) {
	_observers.remove(observer)
}


template <class T>
void Observable<T>::update(const T& newData) const {
	for (auto o: _observers) {
		if (o->onUpdate) {
			o->onUpdate(newData);
		}
	}
}


#endif //ARDUI_OBSERVABLE_H
