//
// Created by MStefan99 on 16.12.19.
//

#include <Arduino.h>
#include "ardUI.h"


class mainScreen: public activity {
    void onCreate() override {
        activity::onCreate();
        auto ll = new linearLayout(true);
        auto tv = new textView("Text!");
        auto bv = new buttonView("Button");

        ll->addView(bv);
        ll->addView(tv);
        setRootView(ll);
    }
};


void setup() {
    ardUI::showScreen<mainScreen>();
}


void loop() {

}
