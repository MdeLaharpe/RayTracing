#include "hittables/HittableList.h"

namespace rt
{
	bool HittableList::BuildAABB(float tMin, float tMax, maths::AABB& outAABB) const
	{
		const size_t size = list.size();
		if (size <= 0 || !list[0]->BuildAABB(tMin, tMax, outAABB))
			return false;

		maths::AABB hittableAABB;
		for (size_t i = 1; i < size; i++)
		{
			if (!list[i]->BuildAABB(tMin, tMax, hittableAABB))
				return false;
			outAABB = Bound(outAABB, hittableAABB);
		}

		return true;
	}

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