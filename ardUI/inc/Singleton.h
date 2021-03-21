//
// Created by MStefan99 on 16.11.20.
//

#ifndef ARDUI_SINGLETON_H
#define ARDUI_SINGLETON_H

template <class T>
class Singleton {
public:
	Singleton() = default;
	explicit Singleton(const Singleton<T>&) = delete;
	virtual ~Singleton() = default;

	Singleton<T>& operator =(const Singleton<T>) = delete;

	T& operator ()();
	static T& getInstance();
};


template <class T>
T& Singleton<T>::getInstance() {
	static T instance;
	return instance;
}


template <class T>
T& Singleton<T>::operator ()() {
	return getInstance();
}


#endif //ARDUI_SINGLETON_H
