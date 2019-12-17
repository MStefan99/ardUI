//
// Created by MStefan99 on 16.12.19.
//

#include "screen.h"


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
