//
// Created by MStefan99 on 16.12.19.
//

#include "screen.h"


void screen::setContentView() {
    //TODO: populate the viewList from xml or layout class
    draw();
}


void screen::addView(view* view) {
    viewList.append(view);
    draw();
}


void screen::onCreate() {
    draw();
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


void screen::draw() const {
    for (auto *v : viewList) {
        v->draw();
    }
}
