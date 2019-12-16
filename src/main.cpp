//
// Created by MStefan99 on 16.12.19.
//

#include <Arduino.h>
#include "ardUI.h"
#include "screen.h"

class mainScreen : public screen {
    void onCreate() override {
        //Do something
    }
};


void setup() {
    ardUI::show<mainScreen>();
}


void loop() {

}
