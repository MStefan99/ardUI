//
// Created by MStefan99 on 20.10.20.
//

#include "Bundle.h"


template <class T>
Bundle::Model<T>::Model(T dataToStore):
	object {dataToStore} {
}


void Bundle::putInt(const String& key, int value) {
	bundleMap[key] = new Model<int>{value};
}


void Bundle::putFloat(const String& key, float value) {
	bundleMap[key] = new Model<float>(value);
}


void Bundle::putString(const String& key, String& value) {
	bundleMap[key] = new Model<String>(value);
}


int Bundle::getInt(const String& key) {
	return ((Model<int>*)bundleMap[key])->object;
}


float Bundle::getFloat(const String& key) {
	return ((Model<float>*)bundleMap[key])->object;
}


//String& Bundle::getString(const String& key) {
//	return;
//}


template <class DataClass>
void Bundle::remove(const String& key) {
	delete (DataClass)bundleMap[key];
	bundleMap.erase(key);
}


template <class DataClass>
void Bundle::put(const String& key, const DataClass& data) {
	bundleMap[key] = &data;
}


template <class DataClass>
DataClass& Bundle::get(const String& key) {
	return *(DataClass*)bundleMap[key];
}


Bundle::~Bundle() {
	for (const auto& pair : bundleMap) {
		auto concept = pair.second;
		delete concept;
	}
}
