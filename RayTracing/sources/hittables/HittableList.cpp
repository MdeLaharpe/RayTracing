#include "hittables/HittableList.h"

namespace rt
{
	bool HittableList::Hit(const maths::Ray& r, float tMin, float tMax, HitRecord& rec) const
	{
		HitRecord tempRec;
		bool hitAnything = false;
		float closestHit = tMax;

		const size_t size = list.size();
		for (size_t i = 0; i < size; i++)
		{
			if (list[i]->Hit(r, tMin, closestHit, tempRec))
			{
				hitAnything = true;
				closestHit = tempRec.t;
				rec = tempRec;
			}
		}

		return hitAnything;
	}
}