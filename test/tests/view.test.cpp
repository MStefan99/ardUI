//
// Created by MStefan99 on 14.7.21.
//

#include "Tester.h"

#include "Event.h"
#include "View.h"


size_t CLICK_COUNT {0};
size_t LONG_CLICK_COUNT {0};


int main() {
	typedef View::MeasureSpec MeasureSpec;

	View* v {nullptr};

	test("MeasureSpec test", []() -> void {

		MeasureSpec measureSpec1 {0};
		MeasureSpec measureSpec2 {50, MeasureSpec::AT_MOST};
		MeasureSpec measureSpec3 {100, MeasureSpec::EXACTLY};

		expect(measureSpec1.getSize()).toEqual(0);
		expect(measureSpec2.getSize()).toEqual(50);
		expect(measureSpec3.getSize()).toEqual(100);

		expect(measureSpec1.getMode()).toEqual(MeasureSpec::UNSPECIFIED);
		expect(measureSpec2.getMode()).toEqual(MeasureSpec::AT_MOST);
		expect(measureSpec3.getMode()).toEqual(MeasureSpec::EXACTLY);
	});

	describe("View test", [&](TestSuite& suite) -> void {
		suite.beforeEach([&]() -> void {
			v = new View;
		});

		suite.afterEach([&]() -> void {
			delete v;
		});

		suite.test("Find By ID", [&]() -> void {
			expect(v->findViewById(v->getId())).toEqual(v);
		});

		suite.test("Measure", [&]() -> void {
			v->measure(MeasureSpec {100, MeasureSpec::EXACTLY},
					MeasureSpec {100, MeasureSpec::EXACTLY});

			expect(v->getMeasuredWidth()).toEqual(100);
			expect(v->getMeasuredHeight()).toEqual(100);

			expect(v->getWidth()).toEqual(0);
			expect(v->getHeight()).toEqual(0);
			expect(v->getBounds().left).toEqual(0);
			expect(v->getBounds().top).toEqual(0);
			expect(v->getBounds().right).toEqual(0);
			expect(v->getBounds().bottom).toEqual(0);
		});

		suite.test("Layout", [&]() -> void {
			v->layout(100, 100, 200, 200);

			expect(v->getBounds().left).toEqual(100);
			expect(v->getBounds().top).toEqual(100);
			expect(v->getBounds().right).toEqual(200);
			expect(v->getBounds().bottom).toEqual(200);

			v->setLeft(200);
			v->setTop(200);
			v->setRight(300);
			v->setBottom(300);

			expect(v->getBounds().left).toEqual(200);
			expect(v->getBounds().top).toEqual(200);
			expect(v->getBounds().right).toEqual(300);
			expect(v->getBounds().bottom).toEqual(300);
		});

		suite.test("Draw", [&]() -> void {
			expect(v->isValid()).toBeFalsy();
			v->draw();
			expect(v->isValid()).toBeTruthy();
			v->invalidate();
			expect(v->isValid()).toBeFalsy();
		});

		suite.test("Event handling", [&]() -> void {
			Event e;

			v->setOnClickListener([](View* v) -> void {
				++CLICK_COUNT;
			});

			v->setOnLongClickListener([](View* v) -> void {
				++LONG_CLICK_COUNT;
			});

			expect(CLICK_COUNT).toEqual(0);
			expect(LONG_CLICK_COUNT).toEqual(0);

			e._currentAction = Event::CLICK;
			v->handleEvent(e);
			expect(CLICK_COUNT).toEqual(1);

			e._currentAction = Event::LONG_CLICK;
			v->handleEvent(e);

			expect(LONG_CLICK_COUNT).toEqual(1);
		});
	});
}
