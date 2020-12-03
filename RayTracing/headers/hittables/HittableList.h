#ifndef RT_HITTABLELIST_H
#define RT_HITTABLELIST_H

#include "hittables/Hittable.h"

namespace rt
{
	class HittableList : public Hittable
	{
	public:
		constexpr HittableList() : list(nullptr), size(0) { }
		constexpr HittableList(Hittable** list, size_t size) : list(list), size(size) { }

		virtual ~HittableList();

		Hittable** list;
		size_t size;

		bool Hit(const maths::Ray& r, float tMin, float tMax, HitRecord& rec) const override;
	};
}

#endif RT_HITTABLELIST_H