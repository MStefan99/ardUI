//
// Created by MStefan99 on 14.7.21.
//

#include "Tester.h"

#include "Event.h"
#include "View.h"


size_t CLICK_COUNT {0};
size_t LONG_CLICK_COUNT {0};
size_t SCROLL_COUNT {0};


struct TestWrapper {
	static void run() {
		typedef View::MeasureSpec MeasureSpec;

		View* v {nullptr};

		test("MeasureSpec test", [] {

			MeasureSpec measureSpec1 {0, MeasureSpec::UNSPECIFIED};
			MeasureSpec measureSpec2 {50, MeasureSpec::AT_MOST};
			MeasureSpec measureSpec3 {100, MeasureSpec::EXACTLY};

			expect(measureSpec1.getSize()).toEqual(0);
			expect(measureSpec2.getSize()).toEqual(50);
			expect(measureSpec3.getSize()).toEqual(100);

			expect(measureSpec1.getMode()).toEqual(MeasureSpec::UNSPECIFIED);
			expect(measureSpec2.getMode()).toEqual(MeasureSpec::AT_MOST);
			expect(measureSpec3.getMode()).toEqual(MeasureSpec::EXACTLY);
		});

		describe("View test", [&](TestSuite& suite) {
			suite.beforeEach([&] {
				v = new View;
			});

			suite.afterEach([&] {
				delete v;
			});

			suite.test("Find By ID", [&] {
				expect(v->findViewById(v->getId())).toEqual(v);
				expect(v->findViewById(v->getId() + 1)).toBeFalsy();
			});

			suite.test("Measure", [&] {
				v->measure(MeasureSpec {100, MeasureSpec::EXACTLY},
						MeasureSpec {200, MeasureSpec::EXACTLY});

				expect(v->getMeasuredWidth()).toEqual(100);
				expect(v->getMeasuredHeight()).toEqual(200);

				expect(v->getWidth()).toEqual(0);
				expect(v->getHeight()).toEqual(0);
				expect(v->getBounds().left).toEqual(0);
				expect(v->getBounds().top).toEqual(0);
				expect(v->getBounds().right).toEqual(0);
				expect(v->getBounds().bottom).toEqual(0);
			});

			suite.test("Layout", [&] {
				v->layout(10, 20, 30, 40);

				expect(v->getBounds().left).toEqual(10);
				expect(v->getBounds().top).toEqual(20);
				expect(v->getBounds().right).toEqual(30);
				expect(v->getBounds().bottom).toEqual(40);

				v->layout({40, 30, 20, 10});

				expect(v->getBounds().left).toEqual(40);
				expect(v->getBounds().top).toEqual(30);
				expect(v->getBounds().right).toEqual(20);
				expect(v->getBounds().bottom).toEqual(10);

				v->setLeft(20);
				v->setTop(30);
				v->setRight(40);
				v->setBottom(50);

				expect(v->getBounds().left).toEqual(20);
				expect(v->getBounds().top).toEqual(30);
				expect(v->getBounds().right).toEqual(40);
				expect(v->getBounds().bottom).toEqual(50);
			});

			suite.test("Draw", [&] {
				expect(v->isValid()).toBeFalsy();
				v->draw();
				expect(v->isValid()).toBeTruthy();
				v->invalidate();
				expect(v->isValid()).toBeFalsy();
			});

			suite.test("Event handling", [&] {
				Event e;

				v->setOnClickListener([](View* v) {
					++CLICK_COUNT;
				});

				v->setOnLongClickListener([](View* v) {
					++LONG_CLICK_COUNT;
				});

				v->setOnScrollListener([](View* v) {
					++SCROLL_COUNT;
				});

				expect(CLICK_COUNT).toEqual(0);
				expect(LONG_CLICK_COUNT).toEqual(0);

				e._currentAction = Event::CLICK;
				v->handleEvent(e);
				expect(CLICK_COUNT).toEqual(1);

				e._currentAction = Event::LONG_CLICK;
				v->handleEvent(e);

				expect(LONG_CLICK_COUNT).toEqual(1);

				e._currentAction = Event::SCROLL;
				v->handleEvent(e);

				expect(SCROLL_COUNT).toEqual(1);
			});

			suite.test("Get default size", [&] {
				MeasureSpec m1 {50, MeasureSpec::UNSPECIFIED};
				MeasureSpec m2 {60, MeasureSpec::AT_MOST};
				MeasureSpec m3 {70, MeasureSpec::EXACTLY};

				expect(View::getDefaultSize(10, m1)).toEqual(10);
				expect(View::getDefaultSize(20, m2)).toEqual(20);
				expect(View::getDefaultSize(30, m3)).toEqual(70);
			});
		});
	}
};


int main() {
	TestWrapper::run();
}
