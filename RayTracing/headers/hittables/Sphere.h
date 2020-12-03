#ifndef RT_SPHERE_H
#define RT_SPHERE_H

#include "hittables\Hittable.h"
#include "maths\Vec3.h"
#include "maths\Ray.h"

namespace rt
{
	class Sphere : public Hittable
	{
	public:
		constexpr Sphere() : center(), radius(1.f) { }
		constexpr Sphere(const maths::Vec3& center, float radius)
			: center(center), radius(radius)
		{ }

		maths::Vec3 center;
		float radius;

		bool hit(const maths::Ray& r, float tMin, float tMax, HitRecord& rec) const override;
	};
}

#endif RT_SPHERE_H