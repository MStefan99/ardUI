//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_ACTIVITY_H
#define ARDUI_ACTIVITY_H


#include "event.h"
#include "view.h"


class Activity {
public:
	Activity() = default;
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

	View* findViewById(int id);

	friend class ardUI;

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

	State currentState {LAUNCHED};
	View* rootView {};
};

#endif //ARDUI_ACTIVITY_H
