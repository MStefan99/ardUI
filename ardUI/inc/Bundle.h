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
	Bundle& operator =(const Bundle& other);

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
	MAP<String, Concept*> bundleMap {};

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

		T object;
	};
};


template <class T>
Bundle::Model<T>::Model(T value):
	object {value} {
}


template <class T>
Bundle::Model<T>* Bundle::Model<T>::copy() {
	return new Model<T> {object};
}


template <class T>
void Bundle::put(const String& key, const T& value) {
	bundleMap[key] = new Model<T> {value};
}


template <class T>
T& Bundle::get(const String& key) {
	return ((Model<T>*)bundleMap[key])->object;
}


template <class T>
void Bundle::remove(const String& key) {
	delete (T*)bundleMap[key];
	bundleMap.erase(key);
}


#endif //ARDUI_BUNDLE_H
