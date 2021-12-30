//
// Created by MStefan99 on 20.10.20.
//

#include "Bundle.h"


Bundle::Concept::~Concept() = default;


Bundle::Bundle(const Bundle& b): _bundleMap(b._bundleMap) {
	for (auto& e: _bundleMap) {
		e.second = e.second->copy();
	}
}


Bundle& Bundle::operator=(const Bundle& other) {
	for (const auto& e: other._bundleMap) {
		_bundleMap[e.first] = e.second->copy();
	}
	return *this;
}


void Bundle::putInt(const String& key, int value) {
	_bundleMap[key] = new Model<int> {value};
}


void Bundle::putFloat(const String& key, float value) {
	_bundleMap[key] = new Model<float> {value};
}


void Bundle::putString(const String& key, const String& value) {
	_bundleMap[key] = new Model<String> {value};
}


int Bundle::getInt(const String& key) {
	return (static_cast<Model<int>*>(_bundleMap[key]))->_object;
}


float Bundle::getFloat(const String& key) {
	return (static_cast<Model<float>*>(_bundleMap[key]))->_object;
}


String& Bundle::getString(const String& key) {
	return (static_cast<Model<String>*>(_bundleMap[key]))->_object;
}


Bundle::~Bundle() {
	for (const auto& e : _bundleMap) {
		delete e.second;
	}
}
