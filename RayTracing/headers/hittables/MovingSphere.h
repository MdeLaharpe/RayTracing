#ifndef RT_MOVINGSPHERE_H
#define RT_MOVINGSPHERE_H

#include "hittables/Hittable.h"
#include "maths/Vec3.h"
#include "materials/Material.h"

namespace rt
{
	class MovingSphere : public Hittable
	{
	public:
		constexpr MovingSphere() : center0(), center1(), time0(0.f), time1(1.f), radius(1.f), material(nullptr) { }
		MovingSphere(const maths::Vec3& center0, const maths::Vec3& center1, float time0, float time1, float radius, std::shared_ptr<const Material> material)
			: center0(center0), center1(center1), time0(time0), time1(time1), radius(radius), material(std::move(material)) { }

		virtual ~MovingSphere() { }

		bool BuildAABB(float tMin, float tMax, maths::AABB& outAABB) const override;
		bool Hit(const maths::Ray& r, float tMin, float tMax, HitRecord& rec) const override;

	private:
		maths::Vec3 CenterAt(float t) const;

		maths::Vec3 center0, center1;
		float time0, time1;
		float radius;
		std::shared_ptr<const Material> material;
	};
}

#endif RT_MOVINGSPHERE_H