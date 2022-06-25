//
// Created by MStefan99 on 28.7.21.
//

#ifndef ARDUI_DIALOG_HPP
#define ARDUI_DIALOG_HPP

#include "platform.hpp"
#include "View.hpp"
#include "Event.hpp"


class Activity;


class Dialog {
S_PUBLIC:
	Dialog() = default;
	virtual ~Dialog() = default;

	Activity* getOwnerActivity();

	void setRootView(View* view);

	friend class Activity;

S_PROTECTED:
	virtual void onCreate();
	virtual void onStop();

S_PRIVATE:
	void measure(View::MeasureSpec widthMeasureSpec, View::MeasureSpec heightMeasureSpec);
	void layout(int16_t left, int16_t top, int16_t right, int16_t bottom);
	void draw() const;
	View* handleEvent(const Event& event);

	Activity* _ownerActivity {nullptr};
	View* _rootView {nullptr};
};

#endif //ARDUI_DIALOG_HPP
