//
// Created by MStefan99 on 20.12.19.
//

#ifndef ARDUI_DRAWABLE_H
#define ARDUI_DRAWABLE_H

#include "platform.h"
#include "rect.h"
#include "llpi.h"


class drawable {
public:
	drawable() = default;
	~drawable() = default;

	virtual void draw() = 0;

	rect copyBounds() const;
	void copyBounds(rect& r) const;
	rect getBounds() const;
	void setBounds(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom);
	void setBounds(const rect& bounds);

	int getLevel();
	bool setLevel(uint16_t level);

	bool getPadding(rect& padding) const;
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
	virtual void onBoundsChange(const rect& bounds);
	virtual bool onLevelChange(uint16_t level);

	bool valid {false};
	bool visible {true};

	rect viewBox {};
	rect padding {};
	uint16_t minHeight {20};
	uint16_t minWidth {20};
	uint16_t level {0};
};

#endif //ARDUI_DRAWABLE_H
