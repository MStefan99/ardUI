//
// Created by MStefan99 on 20.10.20.
//

#ifndef ARDUI_BUNDLE_H
#define ARDUI_BUNDLE_H

#include "platform.h"
#include MAP_H


class Bundle {
protected:
	class Concept;

public:
	Bundle() = default;
	Bundle(const Bundle& b);
	Bundle& operator=(const Bundle& other);

	void putInt(const String& key, int value);
	void putFloat(const String& key, float value);
	void putString(const String& key, const String& value);

	int getInt(const String& key);
	float getFloat(const String& key);
	String& getString(const String& key);

	template <class T>
	void put(const String& key, const T& value);

	template <class T>
	T& get(const String& key);

	template <class T>
	void remove(const String& key);

	~Bundle();

protected:
	TL_NS::map<String, Concept*> _bundleMap {};

	class Concept {
	public:
		virtual ~Concept();
		virtual Concept* copy() = 0;
	};

	template <class T>
	class Model: public Concept {
	public:
		explicit Model<T>(T value);
		Model<T>* copy() override;

		T _object;
	};
};


template <class T>
Bundle::Model<T>::Model(T value):
		_object {value} {
}


template <class T>
Bundle::Model<T>* Bundle::Model<T>::copy() {
	return new Model<T> {_object};
}


template <class T>
void Bundle::put(const String& key, const T& value) {
	_bundleMap[key] = new Model<T> {value};
}


template <class T>
T& Bundle::get(const String& key) {
	return (static_cast<Model<T>*>(_bundleMap[key]))->_object;
}


template <class T>
void Bundle::remove(const String& key) {
	delete static_cast<T*>(_bundleMap[key]);
	_bundleMap.erase(key);
}


#endif //ARDUI_BUNDLE_H
