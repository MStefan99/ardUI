//
// Created by MStefan99 on 13.7.21.
//

#include "AssertException.hpp"


AssertException::AssertException(std::string description) noexcept:
		_desc {std::move(description)} {
	// Nothing to do
}


AssertException::AssertException(const AssertException& e) noexcept:
		_desc {e._desc} {
	// Nothing to do
}


const char* AssertException::what() const noexcept {
	return _desc.c_str();
}
