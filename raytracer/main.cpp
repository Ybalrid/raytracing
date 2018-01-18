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
	Vector3f a{ 1,2,3 };
	Vector3f b{ 3,2,1 };

	std::cout << (a + b) * 2 << '\n';

	hang();
	return 0;
}