//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_ACTIVITY_H
#define ARDUI_ACTIVITY_H


#include "list.h"
#include "view.h"
#include "layout_inflater.h"


class Activity {
public:
	Activity() = default;
	virtual ~Activity();

	template <class compiledLayout>
	void setContentView(compiledLayout layoutClass);
	void setContentView(const String& xmlData);
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
	enum state {
		Launched,
		Created,
		Restarted,
		Started,
		Resumed,
		Paused,
		Stopped,
		Destroyed
	};

	void draw() const;
	void measure();
	void layout();
	View* getRootView();

	state currentState {Launched};
	View* rootView {};
};

#endif //ARDUI_ACTIVITY_H
