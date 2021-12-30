//
// Created by MStefan99 on 28.7.21.
//

#ifndef ARDUI_DIALOG_H
#define ARDUI_DIALOG_H

#include "platform.h"
#include "View.h"
#include "Event.h"


class Activity;


class Dialog {
public:
	Dialog() = default;
	virtual ~Dialog() = default;

	Activity* getOwnerActivity();

	void setRootView (View* view);

	friend class Activity;

protected:
	virtual void onCreate();
	virtual void onStop();

private:
	void measure(View::MeasureSpec widthMeasureSpec, View::MeasureSpec heightMeasureSpec);
	void layout(int16_t left, int16_t top, int16_t right, int16_t bottom);
	void draw() const;
	View* handleEvent(const Event& event);

	Activity* _ownerActivity {nullptr};
	View* _rootView {nullptr};
};

#endif //ARDUI_DIALOG_H
