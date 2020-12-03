#ifndef RT_SPHERE_H
#define RT_SPHERE_H

#include "hittables/Hittable.h"
#include "maths/Vec3.h"
#include "maths/Ray.h"
#include "materials/Material.h"

namespace rt
{
	class Sphere : public Hittable
	{
	public:
		constexpr Sphere() : center(), radius(1.f), material(nullptr) { }
		constexpr Sphere(const maths::Vec3& center, float radius, Material* material)
			: center(center), radius(radius), material(material)
		{ }

		virtual ~Sphere();

		bool Hit(const maths::Ray& r, float tMin, float tMax, HitRecord& rec) const override;

	private:
		maths::Vec3 center;
		float radius;
		Material* material;
	};
}

#endif RT_SPHERE_H