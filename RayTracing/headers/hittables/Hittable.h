#ifndef RT_HITTABLE_H
#define RT_HITTABLE_H

#include "maths/Ray.h"

namespace rt
{
	struct HitRecord
	{
		HitRecord() : point(), normal(), t(0.f) { }

		maths::Vec3 point;
		maths::Vec3 normal;
		float t;
	};

	class Hittable
	{
	public:
		virtual bool hit(const maths::Ray& r, float tMin, float tMax, HitRecord& rec) const = 0;
	};
}

#endif RT_HITTABLE_H