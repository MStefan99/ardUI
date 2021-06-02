//
// Created by MStefan99 on 31.5.21.
//

#ifndef ARDUI_ADAPTER_H
#define ARDUI_ADAPTER_H

#include "platform.h"
#include LIST_H


template <class T>
class AdapterView;


template <class T>
class Adapter {
public:
	virtual ~Adapter() = default;

	virtual View* getView(int position) const = 0;

	virtual const T& getItem(int position) const = 0;
	virtual int getCount() const = 0;
	virtual bool isEmpty() const = 0;
};

#endif //ARDUI_ADAPTER_H
