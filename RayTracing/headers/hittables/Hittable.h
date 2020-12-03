#ifndef RT_HITTABLE_H
#define RT_HITTABLE_H

#include "maths/Vec3.h"
#include "maths/Ray.h"

namespace rt
{
	struct HitRecord
	{
		HitRecord() : point(), normal(), t(0.f), frontFace(true) { }

		maths::Vec3 point;
		maths::Vec3 normal;
		float t;
		bool frontFace;

		inline void SetFaceNormal(const maths::Ray& r, const maths::Vec3& outwardNormal)
		{
			frontFace = Dot(r.direction, outwardNormal) < 0.f;
			normal = frontFace ? outwardNormal : -outwardNormal;
		}
	};

	class Hittable
	{
	public:
		virtual bool Hit(const maths::Ray& r, float tMin, float tMax, HitRecord& rec) const = 0;
	};
}

#endif RT_HITTABLE_H