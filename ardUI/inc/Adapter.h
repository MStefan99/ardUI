//
// Created by MStefan99 on 31.5.21.
//

#ifndef ARDUI_ADAPTER_H
#define ARDUI_ADAPTER_H

#include "Observable.h"


template <class T>
class Adapter: public Observable<T> {
public:
	virtual ~Adapter() = default;

	virtual View* getView(int position) const = 0;

	virtual int getCount() const = 0;
	virtual bool isEmpty() const = 0;

	virtual void notifyDataSetChanged() const = 0;
};


#endif //ARDUI_ADAPTER_H
