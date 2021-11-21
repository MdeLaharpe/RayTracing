#ifndef RT_HITTABLELIST_H
#define RT_HITTABLELIST_H

#include "hittables/Hittable.h"

#include <vector>

namespace rt
{
	class HittableList : public Hittable
	{
	public:
		HittableList() : list() { }
		HittableList(std::vector<std::shared_ptr<Hittable>>&& list) : list(std::move(list)) { }

		virtual ~HittableList() { }

		virtual bool BuildAABB(float tMin, float tMax, maths::AABB& outAABB) const override;
		virtual bool Hit(const maths::Ray& r, float tMin, float tMax, HitRecord& rec) const override;

	private:
		std::vector<std::shared_ptr<Hittable>> list;
	};
}

#endif RT_HITTABLELIST_H