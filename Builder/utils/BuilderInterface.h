//
// Created by MStefan99 on 16.6.21.
//

#ifndef ARDUI_BUILDERINTERFACE_H
#define ARDUI_BUILDERINTERFACE_H
#ifdef __EMSCRIPTEN__

#include <emscripten/bind.h>

#include "platform.h"
#include LIST_H
#include "View.h"
#include "Activity.h"
#include "ActivityManager.h"


template <class T>
bool IteratorNotEquals(const typename LIST<T>::iterator& x,
		const typename LIST<T>::iterator& y) {
	return x != y;
}


class BuilderInterface {
public:
	Activity* getCurrentActivity() const {
		return ActivityManager::_currentActivity;
	}
};

using namespace emscripten;

EMSCRIPTEN_BINDINGS(BuilderInterface) {
	class_<Rect>("Rect")
			.constructor()
			.constructor<int, int, int, int>()
			.property("left", &Rect::left)
			.property("top", &Rect::top)
			.property("right", &Rect::right)
			.property("bottom", &Rect::bottom)
			.function("height", &Rect::height)
			.function("width", &Rect::width);

	class_<Drawable>("Drawable")
			.property("_valid", &Drawable::_valid)
			.property("_viewBox", &Drawable::_viewBox)
			.property("_padding", &Drawable::_padding)
			.property("_minHeight", &Drawable::_minHeight)
			.property("_minWidth", &Drawable::_minWidth)
			.property("_level", &Drawable::_level);

	class_<View, base<Drawable>>("View")
			.property("_measuredWidth", &View::_measuredWidth)
			.property("_measuredHeight", &View::_measuredHeight)
			.property("_viewId", &View::_viewId)
			.property("_measuredHeight", &View::_measuredHeight)
			.property("_measuredWidth", &View::_measuredWidth)
			.function("invalidate", &View::invalidate);

	class_<ProgressBar, base<View>>("ProgressBar")
			.property("_min", &ProgressBar::_min)
			.property("_max", &ProgressBar::_max)
			.property("_barColor", &ProgressBar::_barColor)
			.property("_backgroundColor", &ProgressBar::_backgroundColor);

	class_<TextView, base<View>>("TextView")
			.constructor()
			.constructor<String>()
			.property("_text", &TextView::_text)
			.property("_textSize", &TextView::_textSize)
			.property("_textColor", &TextView::_textColor)
			.property("_backgroundColor", &TextView::_backgroundColor);

	class_<ButtonView, base<TextView>>("ButtonView")
			.constructor()
			.constructor<String>()
			.property("_borderColor", &ButtonView::_borderColor);

	#if !USE_STL
	class_<LIST<View*>::iterator>("listIterator")
			.function("value", &LIST<View*>::iterator::operator *)
			.function("notEquals", &IteratorNotEquals<View*>)
			.function<internal::DeduceArgumentsTag,
					LIST<View*>::iterator& (LIST<View*>::iterator::*)()>
					("increment", &LIST<View*>::iterator::operator ++);

	class_<LIST<View*>>("list")
			.constructor()
			.function("begin", &LIST<View*>::begin)
			.function("end", &LIST<View*>::end);
	#else
	class_<LIST<View*>::iterator>("listIterator")
			.function("value", &LIST<View*>::iterator::operator *)
			.function("notEquals", &IteratorNotEquals<View*>)
			.function<internal::DeduceArgumentsTag,
					LIST<View*>::iterator& (LIST<View*>::iterator::*)()>
					("increment", &LIST<View*>::iterator::operator ++);

	class_<LIST<View*>>("list")
			.function<internal::DeduceArgumentsTag,
					LIST<View*>::iterator (LIST<View*>::*)()>("begin", &LIST<View*>::begin)
			.function<internal::DeduceArgumentsTag,
					LIST<View*>::iterator(LIST<View*>::*)()>("end", &LIST<View*>::end);
	#endif

	class_<ViewGroup, base<View>>("ViewGroup")
			.property("_viewList", &ViewGroup::_viewList)
			.function("addView", &ViewGroup::addView, allow_raw_pointers())
			.function("removeView", &ViewGroup::removeView, allow_raw_pointers())
			.function("removeViewAt", &ViewGroup::removeViewAt, allow_raw_pointers())
			.function("removeViews", &ViewGroup::removeViews)
			.function("removeAllViews", &ViewGroup::removeAllViews);

	enum_<LinearLayout::Orientation>("LinearLayoutOrientation")
			.value("HORIZONTAL", LinearLayout::Orientation::HORIZONTAL)
			.value("VERTICAL", LinearLayout::Orientation::VERTICAL);

	class_<LinearLayout, base<ViewGroup>>("LinearLayout")
			.constructor()
			.property("_orientation", &LinearLayout::_orientation);

	class_<ConstraintLayout::ConstraintSet>("ConstraintSet")
			.function("connect", &ConstraintLayout::ConstraintSet::connect,
					allow_raw_pointers());

	class_<ConstraintLayout, base<ViewGroup>>("ConstraintLayout")
			.constructor()
			.function("getConstraints", &ConstraintLayout::getConstraints,
					allow_raw_pointers());

	class_<Bundle>("Bundle")
			.constructor();

	class_<Activity>("Activity")
			.property("_backgroundColor", &Activity::_backgroundColor)
			.function("measure", &Activity::measure)
			.function("layout", &Activity::layout)
			.function("draw", &Activity::draw)
			.function("getRootView", &Activity::getRootView,
					allow_raw_pointers());

	class_<BuilderInterface>("BuilderInterface")
			.constructor()
			.function("getCurrentActivity", &BuilderInterface::getCurrentActivity,
					allow_raw_pointers());
}


#endif
#endif //ARDUI_BUILDERINTERFACE_H
