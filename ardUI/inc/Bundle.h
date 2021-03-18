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
	void putInt(const String& key, int value);
	void putFloat(const String& key, float value);
	void putString(const String& key, String& value);

	int getInt(const String& key);
	float getFloat(const String& key);
	String& getString(const String& key);

	template <class DataClass>
	void remove(const String& key);

	template <class DataClass>
	void put(const String& key, const DataClass& data);

	template <class DataClass>
	DataClass& get(const String& key);

	~Bundle();

protected:
	MAP<String, Concept*> bundleMap {};

	class Concept{
	public:
		virtual ~Concept() = default;
	};

	template <class T>
	class Model: public Concept {
	public:
		explicit Model<T>(T dataToStore);
		T object;
	};
};

#endif //ARDUI_BUNDLE_H
