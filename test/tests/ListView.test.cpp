//
// Created by MStefan99 on 19.7.21.
//

#include <string>

#include "Tester.h"
#include "TextView.h"
#include "ArrayAdapter.h"
#include "ListView.h"


class StringAdapter: public ArrayAdapter<std::string> {
	using ArrayAdapter<std::string>::ArrayAdapter;

public:
	View* getView(int position) const override {
		return new TextView(getItem(position));
	}
};


int main() {
	ListView<std::string> l;
	std::string stringArray[] {"1", "2", "3"};
	std::list<std::string> stringList {"1", "2", "3"};
	StringAdapter arrayAdapter {stringArray, 3};
	StringAdapter listAdapter {stringList};

	describe("ListView test", [&](TestSuite& suite) {
		suite.test("Array adapter", [&]() {
			expect(arrayAdapter.isEmpty()).toBeFalsy();

			l.setAdapter(&arrayAdapter);

			l.measure(View::MeasureSpec {100},
					View::MeasureSpec {400});

			expect(l.getAdapter()).toEqual(&arrayAdapter);
			expect(l.getChildCount()).toEqual(3);
			expect(((TextView*)l.getChildAt(0))->getText()).toEqual("1");
		});

		suite.test("List adapter", [&]() {
			expect(arrayAdapter.isEmpty()).toBeFalsy();

			l.setAdapter(&listAdapter);

			l.measure(View::MeasureSpec {100},
					View::MeasureSpec {400});

			expect(l.getAdapter()).toEqual(&listAdapter);
			expect(l.getChildCount()).toEqual(3);
			expect(((TextView*)l.getChildAt(0))->getText()).toEqual("1");
		});
	});

	return 0;
}

