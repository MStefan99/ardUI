//
// Created by MStefan99 on 16.12.19.
//

#include <Arduino.h>
#include "ardUI_setup.h"


class mainScreen : public screen {
    void onCreate() override {
        screen::onCreate();
        textView tv1;
        mainScreen::addView(&tv1);
        tv1.setOnClickListener([](view* view) {
            ((textView*)view)->setText("TextView Clicked!");
        });
    }
};


void setup() {

}


void loop() {

}
