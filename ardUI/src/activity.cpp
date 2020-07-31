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
}


void activity::setContentView(const String& xml) {
    layoutInflater::inflate(xml, *rootView);
}


void activity::setRootView(view *view){
    rootView = view;
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
    return rootView->findViewById(id);
}


view* activity::getRootView() {
    return rootView;
}


void activity::measure() {
    int widthSpec = view::measureSpec::makeMeasureSpec(view::measureSpec::EXACTLY, ardUiDisplayGetWidth());
    int heightSpec = view::measureSpec::makeMeasureSpec(view::measureSpec::EXACTLY, ardUiDisplayGetHeight());
    rootView->measure(widthSpec, heightSpec);
}


void activity::layout() {
    rect display {0, 0, ardUiDisplayGetWidth(), ardUiDisplayGetHeight()};
    rootView->layout(display);
}
