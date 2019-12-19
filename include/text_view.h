//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_TEXT_VIEW_H
#define ARDUI_TEXT_VIEW_H

#include <Arduino.h>
#include "view.h"

class textView : public view {
public:
    textView() = default;
    explicit textView(const String& text);
    textView(const String& text, uint16_t size);
    textView(const String& text, uint16_t size, uint32_t color);
    ~textView() = default;

    void setText(const String& text);
    void append(const String& text);
    void setTextSize(uint16_t size);
    void setCurrentTextColor(uint32_t color);

    String& getText();
    uint16_t getTextSize();
    uint32_t getCurrentTextColor();

    void draw() const override;

private:
    String textString {""};
    uint16_t textSize {10};
    uint32_t textColor {0};
};


#endif //ARDUI_TEXT_VIEW_H
