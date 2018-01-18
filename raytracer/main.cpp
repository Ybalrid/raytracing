#include <iostream>
#include <FreeImage.h>
#include "Vector3.hpp"

void hang()
{
	std::cout << "Press RETURN to continue...";
	std::cin.get();
	std::cin.clear();
}

int main()
{
	hang();
	return 0;
}
