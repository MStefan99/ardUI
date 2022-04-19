//
// Created by MStefan99 on 16.11.20.
//

#ifndef ARDUI_SINGLETON_HPP
#define ARDUI_SINGLETON_HPP

template <class T>
class Singleton {
public:
	explicit Singleton(const Singleton<T>&) = delete;

	Singleton<T>& operator=(const Singleton<T>) = delete;

	static T& getInstance();

protected:
	Singleton() = default;
	~Singleton() = default;
};


template <class T>
T& Singleton<T>::getInstance() {
	static T instance;
	return instance;
}


#endif //ARDUI_SINGLETON_HPP
