//
// Created by MStefan99 on 16.12.19.
//

#include "activity.h"


activity::~activity() {
    delete rootView;
}


template<class compiledLayout>
void activity::setContentView(compiledLayout layoutClass) {
    layoutClass.fill();  // "fill()" function must be present in the compiled layout
    draw();
}


void activity::setContentView(const String& xml) {
    layoutInflater::inflate(xml, *rootView);
    draw();
}


void activity::setRootView(view *view){
    rootView = view;
    draw();
}


void activity::onCreate() {
    currentState = Created;
}


void activity::onStart() {
    currentState = Started;
}


void activity::onRestart() {
    currentState = Restarted;
}


void activity::onResume() {
    currentState = Resumed;
}


void activity::onPause() {
    currentState = Paused;
}


void activity::onStop() {
    currentState = Stopped;
}


void activity::onDestroy() {
    currentState = Destroyed;
}


void activity::draw() const {
    if (rootView) {
        rootView->draw();
    }
}


view* activity::findViewById(int id) {
    static int temp {id};  //TODO: use lambda captures instead of static variables (important)
    static view* foundView {nullptr};

    //TODO: replace forEach with for
    return foundView;
}


view* activity::getRootView() {
    return rootView;
}
