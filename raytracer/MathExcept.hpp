#pragma once

#include <iostream>
#include <exception>

class DivideByZeroExcept : public std::runtime_error
{
public:
	explicit DivideByZeroExcept(const std::string& _Message = "Attempted to divide by zero!")
		: runtime_error(_Message)
	{
		std::cerr << "DivideByZeroExcept: "
			<< exception::what() << '\n';
	}
};
