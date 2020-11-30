#ifndef MATHS_RAY_H
#define MATHS_RAY_H

#include "maths\Vec3.h"

namespace maths
{
	struct Ray
	{
		constexpr Ray() { }
		constexpr Ray(const Vec3& origin, const Vec3& direction)
			: origin(origin), direction(direction)
		{ }

		Vec3 origin;
		Vec3 direction;

		Vec3 at(float t) const
		{
			return origin + direction * t;
		}
	};
}

#endif MATHS_RAY_H