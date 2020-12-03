#include "hittables/HittableList.h"

namespace rt
{
	bool HittableList::hit(const maths::Ray& r, float tMin, float tMax, HitRecord& rec) const
	{
		HitRecord tempRec;
		bool hitAnything = false;
		float closestHit = tMax;

		for (size_t i = 0; i < size; i++)
		{
			if (list[i]->hit(r, tMin, closestHit, tempRec))
			{
				hitAnything = true;
				closestHit = tempRec.t;
				rec = tempRec;
			}
		}

		return hitAnything;
	}
}