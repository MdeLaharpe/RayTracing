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
		constexpr MovingSphere() : MovingSphere({}, {}, 0.f, 0.f, 1.f, nullptr) { }
		constexpr MovingSphere(const maths::Vec3& center0, const maths::Vec3& center1, float time0, float time1, float radius, const Material* material)
			: center0(center0), center1(center1), time0(time0), time1(time1), radius(radius), material(material) { }

		virtual ~MovingSphere();

		bool Hit(const maths::Ray& r, float tMin, float tMax, HitRecord& rec) const override;

		maths::Vec3 center0, center1;
		float time0, time1;
		float radius;
		const Material* material;
	};
}

#endif RT_MOVINGSPHERE_H