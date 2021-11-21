#ifndef MATHS_UTILS_H
#define MATHS_UTILS_H

#include "Vec3.h"

namespace maths
{
	constexpr inline float pi = 3.14159265358979323846f;

	inline float DegToRad(float angleDeg)
	{
		return angleDeg * 0.01745329251994329576923690768489f;
	}

	void SphereSurfaceNormalToPolarCoordinates(const Vec3& normal, float& theta, float& phi);
}

#endif MATHS_UTILS_H