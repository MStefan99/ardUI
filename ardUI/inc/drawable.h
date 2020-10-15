//
// Created by MStefan99 on 20.12.19.
//

#ifndef ARDUI_DRAWABLE_H
#define ARDUI_DRAWABLE_H


#include "platform.h"
#include "rect.h"
#include "llpi.h"


class Drawable {
public:
	Drawable() = default;
	~Drawable() = default;

	virtual void draw() = 0;

	Rect copyBounds() const;
	void copyBounds(Rect& r) const;
	Rect getBounds() const;
	void setBounds(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom);
	void setBounds(const Rect& bounds);

	int getLevel();
	bool setLevel(uint16_t level);

	bool getPadding(Rect& padding) const;
	void setPadding(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom);

	uint16_t getMinimumHeight() const;
	void setMinimumHeight(uint16_t minimumHeight);

	uint16_t getMinimumWidth() const;
	void setMinimumWidth(uint16_t minimumWidth);

	//TODO: add inflaters

	bool isVisible() const;
	bool setVisible(bool visible);

	void invalidateSelf();

protected:
	virtual void onBoundsChange(const Rect& bounds);
	virtual bool onLevelChange(uint16_t level);

	bool valid {false};
	bool visible {true};

	Rect viewBox {};
	Rect padding {};
	uint16_t minHeight {20};
	uint16_t minWidth {20};
	uint16_t level {0};
};

#endif //ARDUI_DRAWABLE_H
