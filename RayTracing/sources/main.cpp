#include <iostream>
#include <fstream>

#include "maths/Vec3.h"

int main(int argc, char* argv[])
{
	const char* outputFileName = "out.ppm";

	const int imageWidth = 256;
	const int imageHeight = 256;

	std::ofstream out;
	out.open(outputFileName, std::ios_base::out | std::ios_base::trunc);
	if (!out.is_open())
	{
		std::cerr << "Could not open file " << outputFileName << " for writing" << std::endl;
		return -1;
	}

	out << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

	for (int j = imageHeight - 1; j >= 0; j--)
	{
		for (int i = 0; i < imageWidth; i++)
		{
			maths::Vec3 color(float(i) / (imageWidth - 1), float(j) / (imageHeight - 1), 0.25f);
			out << static_cast<int>(255.999f * color.x) << ' '
				<< static_cast<int>(255.999f * color.y) << ' '
				<< static_cast<int>(255.999f * color.z) << '\n';
		}
	}

	out.close();

	return 0;
}