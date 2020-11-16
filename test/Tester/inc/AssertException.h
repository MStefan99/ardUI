//
// Created by MStefan99 on 16.11.20.
//

#ifndef ARDUI_ASSERTEXCEPTION_H
#define ARDUI_ASSERTEXCEPTION_H


#include <string>


class AssertException: public std::exception {
public:
	AssertException(const std::string& description) noexcept:
			desc {description} {}

	AssertException(const AssertException& e) noexcept:
			desc {e.desc} {}


	~AssertException() override = default;


	const char* what() const noexcept override {
		return desc.c_str();
	}

private:
	std::string desc {};
};

#endif //ARDUI_ASSERTEXCEPTION_H
