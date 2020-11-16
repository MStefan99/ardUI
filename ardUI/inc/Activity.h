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
	explicit Activity(const Bundle& extras,
									 bool startedForResult = false,
									 int requestCode = -1);
	virtual ~Activity();

	template <class compiledLayout>
	void setContentView(compiledLayout layoutClass);
	void setRootView(View* view);

	template <class ActivityClass>
	void startActivity(const Bundle& extras);
	template <class ActivityClass>
	void startActivityForResult(int requestCode, const Bundle& extras = {});
	void setResult(int resultCode, const Bundle& data = {});

	virtual void onCreate() = 0;
	virtual void onStart();
	virtual void onRestart();
	virtual void onResume();
	virtual void onPause();
	virtual void onStop();
	virtual void onDestroy();
	virtual void onActivityResult(int requestCode, int resultCode,
															 const Bundle& results);

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

	void (* resultCallback)(const Bundle& extras) {};

	State currentState {LAUNCHED};
	View* rootView {};
	Bundle bundle {};
	bool returnsResult {false};
	Bundle resultData {};
	int request {-1};
	int result {-1};
};


template <class ActivityClass>
void Activity::startActivity(const Bundle& extras) {
	ActivityManager::switchActivity<ActivityClass>(extras);
}


template <class ActivityClass>
void Activity::startActivityForResult(int requestCode, const Bundle& extras) {
	ActivityManager::switchActivity<ActivityClass>(extras, true, requestCode);
}


#endif //ARDUI_ACTIVITY_H
