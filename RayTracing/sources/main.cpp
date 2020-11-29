#include <iostream>

#include "maths/Vec3.h"

int main(int argc, char* argv[])
{
	maths::Vec3 v0(4.f, 2.f, 1.f), v1(6.f, -3.f, 2.f);
	v0 += v1;

	std::cout << "v0: " << v0 << std::endl;

	return 0;
}