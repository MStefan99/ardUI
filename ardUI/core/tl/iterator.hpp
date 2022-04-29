//
// Created by MStefan99 on 19.7.21.
//

#ifndef ARDUI_ITERATOR_HPP
#define ARDUI_ITERATOR_HPP

namespace tl {
	namespace _internal {
		struct bidirectional_iterator_tag {
		};

		struct random_access_iterator_tag: public bidirectional_iterator_tag {
		};


		template <class Iterator>
		struct iterator {
			typedef typename Iterator::iterator_category iterator_category;
		};


		template <class Iterator, class Distance>
		void _advance(Iterator& it, Distance n, bidirectional_iterator_tag t) {
			if (n > 0) {
				while (n--) {
					++it;
				}
			} else {
				while (n++) {
					--it;
				}
			}
		}


		template <class Iterator, class Distance>
		void _advance(Iterator& it, Distance n, random_access_iterator_tag t) {
			it += n;
		}
	}


	template <class Iterator, class Distance>
	void advance(Iterator& it, Distance n) {
		_internal::_advance(it, n, typename _internal::iterator<Iterator>::iterator_category());
	}
}

#endif //ARDUI_ITERATOR_HPP
