//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_ACTIVITY_H
#define ARDUI_ACTIVITY_H

#include "platform.h"
#include DISPLAY_H
#include "Color.h"

#include "Event.h"
#include "Bundle.h"
#include "View.h"
#include "ActivityManager.h"


class Activity {
public:
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

	virtual void onCreate() = 0;
	virtual void onStart();
	virtual void onRestart();
	virtual void onResume();
	virtual void onPause();
	virtual void onStop();
	virtual void onDestroy();

	View* findViewById(int id);

	friend class EventManager;

	friend class ActivityManager;

	friend class EmscriptenBindingInitializer_BuilderInterface;

protected:
	const Bundle& getExtras();

private:
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

	void measure(uint16_t widthMeasureSpec, uint16_t heightMeasureSpec);
	void layout(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom);
	void draw() const;
	void handleEvent(const Event& event);
	View* getRootView();

	void rewindState(Activity::State targetState);

	State _currentState {LAUNCHED};
	View* _rootView {};
	Bundle _bundle {};
	Bundle _resultData {};
	int _status {};
	void (* _resultCallback)(int statusCode, Bundle resultData) {nullptr};
	Color _backgroundColor {0xffffff};
};


template <class ActivityClass>
void Activity::startActivity(const Bundle& extras) {
	ActivityManager::startActivity<ActivityClass>(extras);
}


template <class ActivityClass>
void Activity::startActivityForResult(void (* onActivityResult)(int statusCode, Bundle resultData),
		const Bundle& extras) {
	ActivityManager::startActivity<ActivityClass>(extras, onActivityResult);
}


template <class compiledLayout>
void Activity::setContentView() {
	compiledLayout layout {};
	layout.fill(this);  // "void fill(Activity*)" function must be present in the compiled layout
}


#endif //ARDUI_ACTIVITY_H
