//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_ACTIVITY_HPP
#define ARDUI_ACTIVITY_HPP

#include "defaults.hpp"
#include "platform.hpp"
#include DISPLAY_H
#include "Color.hpp"

#include "Event.hpp"
#include "Bundle.hpp"
#include "View.hpp"
#include "Dialog.hpp"
#include "ActivityManager.hpp"


class Activity {
S_PUBLIC:
	Activity() = default;
	Activity(const Bundle& extras,
			void (* onActivityResult)(int statusCode, Bundle resultData));
	virtual ~Activity();

	template <class compiledLayout>
	void setContentView();
	Color getBackgroundColor() const;
	void setBackgroundColor(Color backgroundColor);
	void setRootView(View* view);

	template <class ActivityClass>
	void startActivity(const Bundle& extras = {});
	template <class ActivityClass>
	void startActivityForResult(void (* onActivityResult)(int statusCode, Bundle resultData),
			const Bundle& extras = {});
	void setResult(int statusCode = 0, const Bundle& data = {});
	void finish();

	void showDialog(Dialog* dialog);
	void dismissDialog();

	View* findViewById(int id);

	friend class EventManager;

	friend class ActivityManager;

	#ifdef TEST

	friend class TestWrapper;

	#endif

S_PROTECTED:
	virtual void onCreate() = 0;
	virtual void onStart();
	virtual void onRestart();
	virtual void onResume();
	virtual void onPause();
	virtual void onStop();
	virtual void onDestroy();

	const Bundle& getExtras();

S_PRIVATE:
	enum State {
		LAUNCHED,
		CREATED,
		RESTARTED,
		STARTED,
		RESUMED,
		PAUSED,
		STOPPED,
		DESTROYED
	};

	void create();
	void restart();
	void start();
	void resume();
	void pause();
	void stop();
	void destroy();

	void measure(View::MeasureSpec widthMeasureSpec, View::MeasureSpec heightMeasureSpec);
	void layout(int16_t left, int16_t top, int16_t right, int16_t bottom);
	void draw() const;
	View* handleEvent(const Event& event);
	View* getRootView();

	void rewindState(Activity::State targetState);

	State _currentState {LAUNCHED};
	View* _rootView {};
	Bundle _bundle {};
	Bundle _resultData {};
	Dialog* _dialog {};
	int _status {};
	void (* _resultCallback)(int statusCode, Bundle resultData) {nullptr};
	Color _backgroundColor {DEFAULT_BACKGROUND_COLOR};
};


template <class compiledLayout>
void Activity::setContentView() {
	compiledLayout layout {};
	layout.fill(this);  // "void fill(Activity*)" function must be present in the compiled layout
}


template <class ActivityClass>
void Activity::startActivity(const Bundle& extras) {
	ActivityManager::startActivity<ActivityClass>(extras);
}


template <class ActivityClass>
void Activity::startActivityForResult(void (* onActivityResult)(int statusCode, Bundle resultData),
		const Bundle& extras) {
	ActivityManager::startActivity<ActivityClass>(extras, onActivityResult);
}


#endif //ARDUI_ACTIVITY_HPP
