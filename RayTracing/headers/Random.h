#ifndef RT_RANDOM_H
#define RT_RANDOM_H

#include "maths/Vec3.h"

namespace rt
{
	float Rand01();
	float Rand(float min, float max);
	maths::Vec3 RandInUnitDisk();
	maths::Vec3 RandInUnitSphere();
}

#endif RT_RANDOM_H