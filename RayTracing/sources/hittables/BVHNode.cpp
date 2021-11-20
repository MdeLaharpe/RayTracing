#include "hittables/BVHNode.h"

#include <iostream>
#include <functional>
#include <algorithm>

#include "Random.h"

namespace rt
{
	BVHNode::BVHNode(std::vector<std::shared_ptr<Hittable>>& list, size_t start, size_t end, float time0, float time1)
	{
		size_t span = end - start;

		if (span == 1)
		{
			left = right = list[start];
		}
		else
		{
			size_t axis = static_cast<size_t>(Rand(0, 2));

			std::function<bool(const std::shared_ptr<Hittable>&, const std::shared_ptr<Hittable>&)> predicate = std::bind(
				[time0, time1, axis](const std::shared_ptr<Hittable>& hittable0, const std::shared_ptr<Hittable>& hittable1)
				{
					maths::AABB aabb0, aabb1;
					if (!hittable0->BuildAABB(time0, time1, aabb0))
					{
						std::cerr << "No bounding volume in BVHNode constructor !" << std::endl;
						return true;
					}
					if (!hittable1->BuildAABB(time0, time1, aabb1))
					{
						std::cerr << "No bounding volume in BVHNode constructor !" << std::endl;
						return false;
					}
					return aabb0.minimum[axis] < aabb1.minimum[axis];
				},
				std::placeholders::_1, std::placeholders::_2
			);

			if (span == 2)
			{
				if (predicate(list[start], list[start + 1]))
				{
					left = list[start];
					right = list[start + 1];
				}
				else
				{
					left = list[start + 1];
					right = list[start];
				}
			}
			else
			{
				std::sort(list.begin() + start, list.begin() + end, predicate);

				size_t mid = start + span / 2;
				left = std::make_shared<BVHNode>(list, start, mid, time0, time1);
				right = std::make_shared<BVHNode>(list, mid, end, time0, time1);
			}
		}

		maths::AABB aabbLeft, aabbRight;
		if (left->BuildAABB(time0, time1, aabbLeft) && right->BuildAABB(time0, time1, aabbRight))
			aabb = maths::Bound(aabbLeft, aabbRight);
		else
		{
			constexpr float min = std::numeric_limits<float>::min();
			constexpr float max = std::numeric_limits<float>::max();
			aabb = maths::AABB({ min }, { max });
		}
	}

	bool BVHNode::BuildAABB(float tMin, float tMax, maths::AABB& outAABB) const
	{
		outAABB = aabb;
		return true;
	}

	bool BVHNode::Hit(const maths::Ray& r, float tMin, float tMax, HitRecord& rec) const
	{
		if (!aabb.Hit(r, tMin, tMax))
			return false;

		bool hitLeft = left->Hit(r, tMin, tMax, rec);
		bool hitRight = right->Hit(r, tMin, hitLeft ? rec.t : tMax, rec);
		return hitLeft || hitRight;
	}
}