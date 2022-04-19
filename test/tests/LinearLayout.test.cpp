//
// Created by MStefan99 on 19.7.21.
//

#include "Tester.hpp"

#include "LinearLayout.hpp"


int main() {
	Rect screen {0, 0, 400, 400};
	LinearLayout l;

	for (unsigned int i {0}; i < 3; ++i) {
		l.addView(new View);
	}

	describe("LinearLayout test", [&](TestSuite& suite) {
		suite.test("Orientation", [&] {
			l.setOrientation(LinearLayout::HORIZONTAL);
			expect(l.getOrientation()).toEqual(LinearLayout::HORIZONTAL);

			l.setOrientation(LinearLayout::VERTICAL);
			expect(l.getOrientation()).toEqual(LinearLayout::VERTICAL);
		});

		suite.test("Vertical layout", [&]() {
			l.setOrientation(LinearLayout::VERTICAL);
			l.measure(View::MeasureSpec {screen.width(), View::MeasureSpec::EXACTLY},
					View::MeasureSpec {screen.height()});

			l.layout(screen);

			expect(l.getChildAt(0)->getBounds().top).toEqual(screen.top);
			expect(l.getChildAt(0)->getBounds().left).toEqual(screen.left);
			expect(l.getChildAt(0)->getBounds().right).toEqual(screen.right);
			expect(l.getChildAt(1)->getBounds().top)
					.toEqual(l.getChildAt(0)->getBounds().bottom);
		});

		suite.test("Horizontal layout", [&]() {
			l.setOrientation(LinearLayout::HORIZONTAL);
			l.measure(View::MeasureSpec {screen.width()},
					View::MeasureSpec {screen.height(), View::MeasureSpec::EXACTLY});

			l.layout(screen);

			expect(l.getChildAt(0)->getBounds().left).toEqual(screen.left);
			expect(l.getChildAt(0)->getBounds().top).toEqual(screen.top);
			expect(l.getChildAt(0)->getBounds().bottom).toEqual(screen.bottom);
			expect(l.getChildAt(1)->getBounds().left)
					.toEqual(l.getChildAt(0)->getBounds().right);
		});
	});

	return 0;
}
