#include "maths/AABB.h"

#include <utility>

namespace maths
{
	bool AABB::Hit(const Ray& r, float tMin, float tMax) const
	{
		for (int axis = 0; axis < 3; axis++)
		{
			float invD = 1.f / r.direction[axis];
			float t0 = invD * (minimum[axis] - r.origin[axis]);
			float t1 = invD * (maximum[axis] - r.origin[axis]);

			if (invD < 0.f)
				std::swap(t0, t1);

			tMin = t0 > tMin ? t0 : tMin;
			tMax = t1 < tMax ? t1 : tMax;

			if (tMax <= tMin)
				return false;
		}
		return true;
	}

	AABB Bound(const AABB& aabb0, const AABB& aabb1)
	{
		return AABB(
			Vec3(
				std::min(aabb0.minimum.x, aabb1.minimum.x),
				std::min(aabb0.minimum.y, aabb1.minimum.y),
				std::min(aabb0.minimum.z, aabb1.minimum.z)
			),
			Vec3(
				std::max(aabb0.maximum.x, aabb1.maximum.x),
				std::max(aabb0.maximum.y, aabb1.maximum.y),
				std::max(aabb0.maximum.z, aabb1.maximum.z)
			)
		);

	}
}