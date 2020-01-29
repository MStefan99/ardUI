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
        map() = default;

    protected:
        class element {
        public:
            element();

        private:
            pair<Key, T> content;
            element* left {nullptr};
            element* right {nullptr};
        };

        Comp comp {Comp()};
        element* root {nullptr};
    };
}

#endif //ARDUI_TEST_MAP_H
