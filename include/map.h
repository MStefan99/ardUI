//
// Created by MStefan99 on 29.1.20.
//

#ifndef ARDUI_TEST_MAP_H
#define ARDUI_TEST_MAP_H

#include "pair.h"
#include "less.h"

namespace ardui {
    template <class Key, class T, class Comp = less<T>>
    class map {
    public:
        class iterator {  // bidirectional iterator

        };

        map() = default;

    protected:
        class element {
        public:
            element() = default;

        private:
            pair<Key, T> value;
            element* left {nullptr};
            element* right {nullptr};
        };

        element* root {nullptr};
    };
}

#endif //ARDUI_TEST_MAP_H
