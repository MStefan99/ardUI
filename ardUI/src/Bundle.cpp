//
// Created by MStefan99 on 20.10.20.
//

#include "Bundle.h"


void Bundle::putInt(const String& key, int value) {
	bundleMap[key] = new Model<int>{value};
}


void Bundle::putFloat(const String& key, float value) {
	bundleMap[key] = new Model<float>(value);
}


void Bundle::putString(const String& key, const String& value) {
	bundleMap[key] = new Model<String>(value);
}


int Bundle::getInt(const String& key) {
	return ((Model<int>*)bundleMap[key])->object;
}


float Bundle::getFloat(const String& key) {
	return ((Model<float>*)bundleMap[key])->object;
}


String& Bundle::getString(const String& key) {
	return ((Model<String>*)bundleMap[key])->object;
}


Bundle::~Bundle() {
	for (const auto& pair : bundleMap) {
		auto concept = pair.second;
		delete concept;
	}
}
