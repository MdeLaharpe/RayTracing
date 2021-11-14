#include "maths/AABB.h"

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
}