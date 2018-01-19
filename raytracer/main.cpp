#include <iostream>
#include <FreeImage.h>
#include "Vector3.hpp"
#include "Image.hpp"

void initFreeImage()
{
	std::cout << FreeImage_GetCopyrightMessage() << '\n';

	//give a function to print the errors for free image
	FreeImage_SetOutputMessage([](FREE_IMAGE_FORMAT fif, const char* message)
	{
		std::cout << "\n***";
		if (fif != FIF_UNKNOWN) std::cout << FreeImage_GetFormatFromFIF(fif) << " Format\n";
		std::cout << message;
		std::cout << " ***\n";
	});
}

void hang()
{
	std::cout << "Press RETURN to continue...";
	std::cin.get();
	std::cin.clear();
}

int main()
{
	initFreeImage();

	hang();
	return 0;
}
