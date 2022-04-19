//
// Created by MStefan99 on 19.7.21.
//

#include <vector>

#include "Tester.hpp"

#include "ConstraintLayout.hpp"


int main() {
	std::vector<View*> views;
	ConstraintLayout l {};
	auto c {l.getConstraints()};
	Rect screen {0, 0, 400, 400};

	for (unsigned int i {0}; i < 4; ++i) {
		auto v {new View};
		views.push_back(v);
		l.addView(v);
	}

	describe("ConstraintLayout test", [&](TestSuite& suite) {
		suite.test("Single side constraints", [&] {
			c->connect(views[0], ConstraintLayout::LEFT, &l, ConstraintLayout::LEFT, 2);
			c->connect(views[1], ConstraintLayout::TOP, &l, ConstraintLayout::TOP, 4);
			c->connect(views[2], ConstraintLayout::RIGHT, &l, ConstraintLayout::RIGHT, 8);
			c->connect(views[3], ConstraintLayout::BOTTOM, &l, ConstraintLayout::BOTTOM, 16);

			l.measure(View::MeasureSpec {screen.width(), View::MeasureSpec::EXACTLY},
					View::MeasureSpec {screen.height(), View::MeasureSpec::EXACTLY});

			l.layout(screen);

			expect(views[0]->getBounds().left).toEqual(screen.left + 2);
			expect(views[1]->getBounds().top).toEqual(screen.top + 4);
			expect(views[2]->getBounds().right).toEqual(screen.right - 8);
			expect(views[3]->getBounds().bottom).toEqual(screen.bottom - 16);

			expect(views[0]->getWidth()).toEqual(views[0]->getMinimumWidth());
			expect(views[1]->getWidth()).toEqual(views[1]->getMinimumWidth());
			expect(views[2]->getWidth()).toEqual(views[2]->getMinimumWidth());
			expect(views[3]->getWidth()).toEqual(views[3]->getMinimumWidth());

			expect(views[0]->getHeight()).toEqual(views[0]->getMinimumHeight());
			expect(views[1]->getHeight()).toEqual(views[1]->getMinimumHeight());
			expect(views[2]->getHeight()).toEqual(views[2]->getMinimumHeight());
			expect(views[3]->getHeight()).toEqual(views[3]->getMinimumHeight());
		});

		suite.test("Two-side constraints", [&] {
			c->connect(views[0], ConstraintLayout::RIGHT, &l, ConstraintLayout::RIGHT, 16);
			c->connect(views[1], ConstraintLayout::BOTTOM, &l, ConstraintLayout::BOTTOM, 8);
			c->connect(views[2], ConstraintLayout::LEFT, &l, ConstraintLayout::LEFT, 4);
			c->connect(views[3], ConstraintLayout::TOP, &l, ConstraintLayout::TOP, 2);

			l.measure(View::MeasureSpec {screen.width(), View::MeasureSpec::EXACTLY},
					View::MeasureSpec {screen.height(), View::MeasureSpec::EXACTLY});

			l.layout(screen);

			expect(views[0]->getBounds().left).toEqual(screen.left + 2);
			expect(views[1]->getBounds().top).toEqual(screen.top + 4);
			expect(views[2]->getBounds().right).toEqual(screen.right - 8);
			expect(views[3]->getBounds().bottom).toEqual(screen.bottom - 16);

			expect(views[0]->getBounds().right).toEqual(screen.right - 16);
			expect(views[1]->getBounds().bottom).toEqual(screen.bottom - 8);
			expect(views[2]->getBounds().left).toEqual(screen.left + 4);
			expect(views[3]->getBounds().top).toEqual(screen.top + 2);

			expect(views[0]->getWidth()).toEqual(screen.width() - 18);
			expect(views[1]->getHeight()).toEqual(screen.height() - 12);
			expect(views[2]->getWidth()).toEqual(screen.width() - 12);
			expect(views[3]->getHeight()).toEqual(screen.height() - 18);
		});
	});

	return 0;
}
