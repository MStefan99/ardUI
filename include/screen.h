//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_SCREEN_H
#define ARDUI_SCREEN_H


#include "slist.h"
#include "view.h"
#include "layout_inflater.h"


class screen {
public:
    screen() = default;
    virtual ~screen();

    template <class compiledLayout>
    void setContentView(compiledLayout layoutClass);
    void setContentView(const String& xmlData);
    void setRootView(view* view);

    virtual void onCreate() = 0;
    virtual void onStart();
    virtual void onRestart();
    virtual void onResume();
    virtual void onPause();
    virtual void onStop();
    virtual void onDestroy();

    void draw() const;
    view* findViewById(int id);

    friend class ardUI;

private:
    virtual void create();
    virtual void start();
    virtual void restart();
    virtual void resume();
    virtual void pause();
    virtual void stop();
    virtual void destroy();
    
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

    state currentState {Launched};
    view* getRootView();
    view* rootView {};
};

#endif //ARDUI_SCREEN_H
