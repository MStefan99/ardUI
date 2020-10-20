//
// Created by MStefan99 on 20.10.20.
//

#ifndef ARDUI_BUNDLE_H
#define ARDUI_BUNDLE_H


#include "platform.h"
#include MAP_H


class Bundle {
public:
	void putInt(const String& key, int value);
	void putIntArray(const String& key, int* value);
	void putFloat(const String& key, float value);
	void putFloatArray(const String& key, float* value);
	void putString(const String& key, String& value);

	int getInt(const String& key);
	int* getIntArray(const String& key);
	float getFloat(const String& key);
	float* getFloatArray(const String& key);
	String& getString(const String& key);

protected:
	MAP<String, void*> bundleMap {};
};

#endif //ARDUI_BUNDLE_H