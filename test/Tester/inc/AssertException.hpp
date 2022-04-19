//
// Created by MStefan99 on 16.11.20.
//

#ifndef ARDUI_ASSERTEXCEPTION_HPP
#define ARDUI_ASSERTEXCEPTION_HPP

#include <string>
#include <utility>


class AssertException: public std::exception {
public:
	explicit AssertException(std::string description) noexcept;
	~AssertException() override = default;

	AssertException(const AssertException& e) noexcept;

	const char* what() const noexcept override;

private:
	std::string _desc {};
};

#endif //ARDUI_ASSERTEXCEPTION_HPP
