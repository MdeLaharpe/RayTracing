#ifndef RT_RANDOM_H
#define RT_RANDOM_H

#include "maths/Vec3.h"

namespace rt
{
	float Rand01();
	float Rand(float min, float max);
	int32_t Rand(int32_t min, int32_t max);
	maths::Vec3 RandInUnitDisk();
	maths::Vec3 RandInUnitSphere();
	maths::Vec3 RandOnUnitSphere();
}

#endif RT_RANDOM_H