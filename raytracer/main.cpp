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

	Image i{ 256, 256 };
	const RGBQUAD green = []
	{
		RGBQUAD color;
		color.rgbBlue = 0;
		color.rgbGreen = 255;
		color.rgbRed = 0;
		return color;
	}();

	const auto w = i.width();
	const auto h = i.height();

	for (size_t y{ 0 }; y < h; ++y)
		for (size_t x{ 0 }; x < w; ++x)
			i.setPixelColor(x, y, green);

	const auto bitmasks = i.colorMask();

	i.save("./output.bmp", FREE_IMAGE_FORMAT::FIF_BMP);
	hang();
	return 0;
}
