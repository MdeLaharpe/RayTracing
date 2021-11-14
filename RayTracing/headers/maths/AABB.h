#ifndef MATHS_AABB_H
#define MATHS_AABB_H

#include "maths/Vec3.h"
#include "maths/Ray.h"

namespace maths
{
	struct AABB
	{
		constexpr AABB() { }
		constexpr AABB(const Vec3& minimum, const Vec3& maximum)
			: minimum(minimum), maximum(maximum) { }

		Vec3 minimum, maximum;

		bool Hit(const Ray& r, float tMin, float tMax) const;
	};
}

#endif MATHS_AABB_H