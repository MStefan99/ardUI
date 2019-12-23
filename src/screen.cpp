//
// Created by MStefan99 on 16.12.19.
//

#include "clickable.h"
#include "screen.h"


screen::~screen() {
    delete rootView;
}


template<class compiledLayout>
void screen::setContentView(compiledLayout layoutClass) {
    layoutClass.fill();  // "fill()" function must be present in the compiled layout
    draw();
}


void screen::setContentView(const String& xml) {
    layoutInflater::inflate(xml, rootView);
    draw();
}


void screen::setRootView(view *view){
    rootView = view;
    draw();
}


void screen::onCreate() {

}


void screen::onStart() {

}


void screen::onRestart() {

}


void screen::onResume() {

}


void screen::onPause() {

}


void screen::onStop() {

}


void screen::onDestroy() {

}


void screen::create() {
    if (currentState == Launched || currentState == Stopped) {
        currentState = Created;
        onCreate();
    }
}


void screen::start() {
    if (currentState == Created || currentState == Restarted) {
        currentState = Started;
        onStart();
    }
}


void screen::restart() {
    if (currentState == Stopped) {
        currentState = Restarted;
        onRestart();
    }
}


void screen::resume() {
    if (currentState == Started || currentState == Paused) {
        currentState = Resumed;
        onResume();
    }
}


void screen::pause() {
    if (currentState == Resumed) {
        currentState = Paused;
        onPause();
    }
}


void screen::stop() {
    if (currentState == Paused) {
        currentState = Stopped;
        onStop();
    }
}


void screen::destroy() {
    if (currentState == Stopped) {
        currentState = Destroyed;
        onDestroy();
    }
}


void screen::draw() const {
    if (rootView) {
        rootView->draw();
    }
}


view* screen::findViewById(int id) {
    static int temp {id};  //TODO: use lambda captures instead of static variables (important)
    static view* foundView {nullptr};

    rootView->forEach([](view* v) {
        if (v->getId() == temp) {
            foundView = v;
        }
    });
    return foundView;
}


view* screen::getRootView() {
    return rootView;
}
