//
// Created by MStefan99 on 14.4.21.
//

#ifndef ARDUI_PROGRESSBAR_H
#define ARDUI_PROGRESSBAR_H

#include "platform.h"
#include "View.h"


class ProgressBar: public View {
public:
	ProgressBar() = default;
	~ProgressBar() override = default;

	uint16_t getProgress() const;
	void setProgress(uint16_t progress);

	uint16_t getMin() const;
	void setMin(uint16_t min);

	uint16_t getMax() const;
	void setMax(uint16_t max);

	Color getBarColor() const;
	void setBarColor(Color barColor);

	Color getBackgroundColor() const;
	void setBackgroundColor(Color backgroundColor);

	friend class EmscriptenBindingInitializer_BuilderInterface;

protected:
	void onDraw() override;

	static uint16_t mapScale(uint16_t value, uint16_t oldMin, uint16_t oldMax, uint16_t newMin, uint16_t newMax);

	Color _barColor {0x0};
	Color _backgroundColor {0xffffff};

	uint16_t _min {};
	uint16_t _max {100};
};

#endif //ARDUI_PROGRESSBAR_H
