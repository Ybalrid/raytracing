#pragma once

#include <exception>
#include <iostream>
#include <string>
#include <sstream>

class ImageCantAllocateExcept : public std::runtime_error
{
public:
	explicit ImageCantAllocateExcept(const std::string& _Message = "Allocating image failed!")
		: runtime_error(_Message)
	{
		std::cout << exception::what() << '\n';
	}
};


class ImageCantLoadExept : public std::runtime_error
{
	std::string path;
public:
	ImageCantLoadExept(const std::string& path, const std::string& _Message = "Loading image from fime Failed")
		: runtime_error(_Message), path{path}
	{
		std::cout << ImageCantLoadExept::what() << std::endl;
	}

	const char* what() const throw() final
	{
		std::ostringstream out;
		out << std::runtime_error::what();
		out << "\nImage path was : " << path << '\n';
		return out.str().c_str();
	}

};