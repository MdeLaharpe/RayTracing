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

		std::vector<std::shared_ptr<Hittable>> list;

		bool Hit(const maths::Ray& r, float tMin, float tMax, HitRecord& rec) const override;
	};
}

#endif RT_HITTABLELIST_H