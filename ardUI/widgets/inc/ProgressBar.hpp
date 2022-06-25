//
// Created by MStefan99 on 14.4.21.
//

#ifndef ARDUI_PROGRESSBAR_H
#define ARDUI_PROGRESSBAR_H

#include "defaults.hpp"
#include "platform.hpp"
#include DISPLAY_H

#include "View.hpp"


class ProgressBar: S_PUBLIC View {
S_PUBLIC:
	ProgressBar() = default;
	~ProgressBar() override = default;

	int16_t getProgress() const;
	void setProgress(int16_t progress);

	int16_t getMin() const;
	void setMin(int16_t min);

	int16_t getMax() const;
	void setMax(int16_t max);

	Color getBarColor() const;
	void setBarColor(Color barColor);

	Color getBackgroundColor() const;
	void setBackgroundColor(Color backgroundColor);

S_PROTECTED:
	void onDraw() override;

	static int16_t mapScale(int16_t value, int16_t oldMin, int16_t oldMax, int16_t newMin, int16_t newMax);

	Color _barColor {DEFAULT_COLOR};
	Color _backgroundColor {DEFAULT_BACKGROUND_COLOR};

	int16_t _min {};
	int16_t _max {100};
};

#endif //ARDUI_PROGRESSBAR_H
