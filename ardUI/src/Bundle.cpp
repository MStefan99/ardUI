//
// Created by MStefan99 on 20.10.20.
//

#include "Bundle.h"


void Bundle::putInt(const String& key, int value) {
	bundleMap[key] = &value;
}


void Bundle::putIntArray(const String& key, int* value) {
	bundleMap[key] = value;
}


void Bundle::putFloat(const String& key, float value) {
	bundleMap[key] = &value;
}


void Bundle::putFloatArray(const String& key, float* value) {
	bundleMap[key] = value;
}


void Bundle::putString(const String& key, String& value) {
	bundleMap[key] = &value;
}


int Bundle::getInt(const String& key) {
	return *(int*)bundleMap[key];
}


int* Bundle::getIntArray(const String& key) {
	return (int*)bundleMap[key];
}


float Bundle::getFloat(const String& key) {
	return *(float*)bundleMap[key];
}


float* Bundle::getFloatArray(const String& key) {
	return (float*)bundleMap[key];
}


String& Bundle::getString(const String& key) {
	return *(String*)bundleMap[key];
}
