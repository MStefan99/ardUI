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
    textView(const String& text, uint16_t x, uint16_t y);
    textView(const String& text, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
    ~textView() override = default;

    void setText(const String& textToSet);
    void append(const String& textToAppend);
    void setTextSize(uint16_t textSize);
    void setTextColor(uint32_t textColor);

    String getText() const;
    uint16_t getTextSize() const;
    uint32_t getTextColor() const;

    void draw() const override;

protected:
    String text {""};
    uint16_t textSize {10};
    uint32_t textColor {0};
};


#endif //ARDUI_TEXT_VIEW_H
