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
#include "TextView.h"
#include "ButtonView.h"
#include "ProgressBar.h"
#include "ViewGroup.h"
#include "Adapter.h"
#include "AdapterView.h"
#include "ListView.h"
#include "LinearLayout.h"
#include "ConstraintLayout.h"
#include "Activity.h"
#include "ActivityManager.h"


#define ENQUOTE(a) #a

#define LIST_VIEW(class) \
  class_<Adapter<class>>(ENQUOTE(class Adapter)); \
  class_<AdapterView<class>, base<ViewGroup>>(ENQUOTE(class AdapterView)); \
  class_<ListView<class>, base<AdapterView<class>>>(ENQUOTE(class ListView)).constructor()


template <class T>
bool IteratorNotEquals(const typename TL_NS::list<T>::iterator& x,
		const typename TL_NS::list:iterator& y) {
	return x != y;
}


class BuilderInterface {
public:
	Activity* getCurrentActivity() const;
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

#if COLOR_MODE == COLOR_888
	class_<Color::ColorData>("ColorData")
			.constructor()
			.property("_r", &Color::ColorData::_r)
			.property("_g", &Color::ColorData::_g)
			.property("_b", &Color::ColorData::_b);
#endif

	class_<Color>("Color")
			.constructor()
			.property("_color", &Color::_color);

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
	class_<TL_NS::list<View*>::iterator>("listIterator")
			.function("value", &TL_NS::list<View*>::iterator::operator *)
			.function("notEquals", &IteratorNotEquals<View*>)
			.function<internal::DeduceArgumentsTag,
					TL_NS::list<View*>::iterator& (TL_NS::list<View*>::iterator::*)()>
					("increment", &TL_NS::list<View*>::iterator::operator ++);

	class_<TL_NS::list<View*>>("list")
			.constructor()
			.function("begin", &TL_NS::list<View*>::begin)
			.function("end", &TL_NS::list<View*>::end);
#else
	class_<TL_NS::list<View*>::iterator>("listIterator")
			.function("value", &TL_NS::list<View*>::iterator::operator*)
			.function("notEquals", &IteratorNotEquals<View*>)
			.function<internal::DeduceArgumentsTag,
					TL_NS::list<View*>::iterator& (TL_NS::list<View*>::iterator::*)()>
					("increment", &TL_NS::list<View*>::iterator::operator++);

	class_<TL_NS::list<View*>>("list")
			.function<internal::DeduceArgumentsTag,
					TL_NS::list<View*>::iterator (TL_NS::list<View*>::*)()>("begin", &TL_NS::list<View*>::begin)
			.function<internal::DeduceArgumentsTag,
					TL_NS::list<View*>::iterator(TL_NS::list<View*>::*)()>("end", &TL_NS::list<View*>::end);
#endif

	class_<ViewGroup, base<View>>("ViewGroup")
			.property("_viewList", &ViewGroup::_viewList)
			.function("addView", &ViewGroup::addView, allow_raw_pointers())
			.function("removeView", &ViewGroup::removeView, allow_raw_pointers())
			.function("removeViewAt", &ViewGroup::removeViewAt, allow_raw_pointers())
			.function("removeViews", &ViewGroup::removeViews)
			.function("removeAllViews", &ViewGroup::removeAllViews);

	LIST_VIEW(String);
	LIST_VIEW(int);
	LIST_VIEW(float);

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
