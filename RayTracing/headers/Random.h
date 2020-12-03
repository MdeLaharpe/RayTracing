#ifndef RT_RANDOM_H
#define RT_RANDOM_H

#include <random>

#include "maths/Vec3.h"

namespace rt
{
	float Rand01();
	maths::Vec3 RandInUnitSphere();
}

#endif RT_RANDOM_H