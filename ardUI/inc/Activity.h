//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_ACTIVITY_H
#define ARDUI_ACTIVITY_H


#include "platform.h"
#include LIST_H

#include "Event.h"
#include "Bundle.h"
#include "View.h"
#include "ActivityManager.h"


class Activity {
public:
	Activity() = default;
	explicit Activity(const Bundle& extras);
	virtual ~Activity();

	template <class compiledLayout>
	void setContentView(compiledLayout layoutClass);
	void setRootView(View* view);

	virtual void onCreate() = 0;
	virtual void onStart();
	virtual void onRestart();
	virtual void onResume();
	virtual void onPause();
	virtual void onStop();
	virtual void onDestroy();
//	virtual void onActivityResult();

	View* findViewById(int id);

	friend class EventManager;

	friend class ActivityManager;

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

	void draw() const;
	void measure();
	void layout();
	void handleEvent(const Event& event);
	View* getRootView();

	void rewindState(Activity::State targetState);

	State currentState {LAUNCHED};
	Bundle bundle {};
	View* rootView {};
	void (* resultCallback)(const Bundle& extras) {};
};


#endif //ARDUI_ACTIVITY_H
