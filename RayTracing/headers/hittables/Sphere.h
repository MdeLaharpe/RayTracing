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
		Sphere(const maths::Vec3& center, float radius, std::shared_ptr<const Material> material)
			: center(center), radius(radius), material(std::move(material))
		{ }

		virtual ~Sphere() { }

		virtual bool BuildAABB(float tMin, float tMax, maths::AABB& outAABB) const override;
		virtual bool Hit(const maths::Ray& r, float tMin, float tMax, HitRecord& rec) const override;

	private:
		maths::Vec3 center;
		float radius;
		std::shared_ptr<const Material> material;
	};
}

#endif RT_SPHERE_H