//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_TEXTVIEW_H
#define ARDUI_TEXTVIEW_H

#include <Arduino.h>
#include "view.h"

class textView : public view {
public:
    void setText(const String& text);
    void append(const String& text);
    void setTextSize(uint16_t size);
    void setCurrentTextColor(uint32_t color);

    String& getText();
    uint16_t getTextSize();
    uint32_t getCurrentTextColor();

    void draw() const override;

private:
    String str = "";
    uint16_t textSize = 0;
    uint32_t clr = 0;
};


#endif //ARDUI_TEXTVIEW_H
