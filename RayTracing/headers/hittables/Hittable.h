#ifndef RT_HITTABLE_H
#define RT_HITTABLE_H

#include <memory>

#include "maths/Vec3.h"
#include "maths/Ray.h"
#include "maths/AABB.h"

namespace rt
{
	class Material;

	struct HitRecord
	{
		constexpr HitRecord() : point(), normal(), t(0.f), frontFace(true), material(nullptr) { }

		maths::Vec3 point;
		maths::Vec3 normal;
		float t;
		bool frontFace;
		std::shared_ptr<const Material> material;

		inline void SetFaceNormal(const maths::Ray& r, const maths::Vec3& outwardNormal)
		{
			frontFace = Dot(r.direction, outwardNormal) < 0.f;
			normal = frontFace ? outwardNormal : -outwardNormal;
		}
	};

	class Hittable
	{
	public:
		virtual ~Hittable() = default;

		virtual bool BuildAABB(float tMin, float tMax, maths::AABB& outAABB) const = 0;
		virtual bool Hit(const maths::Ray& r, float tMin, float tMax, HitRecord& rec) const = 0;
	};
}

#endif RT_HITTABLE_H