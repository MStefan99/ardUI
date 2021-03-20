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
	Activity(const Bundle& extras,
					 void (* onActivityResult)(int statusCode, Bundle resultData));
	virtual ~Activity();

	template <class compiledLayout>
	void setContentView(compiledLayout layoutClass);
	void setRootView(View* view);

	template <class ActivityClass>
	void startActivity(const Bundle& extras);
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

	void draw() const;
	void measure();
	void layout();
	void handleEvent(const Event& event);
	View* getRootView();

	void rewindState(Activity::State targetState);

	State currentState {LAUNCHED};
	View* rootView {};
	Bundle bundle {};
	Bundle resultData {};
	int status {};
	void (* resultCallback)(int statusCode, Bundle resultData) {nullptr};
};


template <class ActivityClass>
void Activity::startActivity(const Bundle& extras) {
	ActivityManager::switchActivity<ActivityClass>(extras);
}


template <class ActivityClass>
void Activity::startActivityForResult(void (* onActivityResult)(int statusCode, Bundle resultData),
																			const Bundle& extras) {
	ActivityManager::switchActivity<ActivityClass>(onActivityResult, extras);
}


#endif //ARDUI_ACTIVITY_H