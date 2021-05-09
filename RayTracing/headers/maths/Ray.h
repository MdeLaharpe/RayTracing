#ifndef MATHS_RAY_H
#define MATHS_RAY_H

#include "maths/Vec3.h"

namespace maths
{
	struct Ray
	{
		constexpr Ray() : time(0.f) { }
		constexpr Ray(const Vec3& origin, const Vec3& direction, float time)
			: origin(origin), direction(direction), time(time)
		{ }

		Vec3 origin;
		Vec3 direction;
		float time;

		Vec3 At(float t) const
		{
			return origin + direction * t;
		}
	};
}

#endif MATHS_RAY_H