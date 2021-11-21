#include "maths/Utils.h"

#include <cmath>

namespace maths
{
	void SphereSurfaceNormalToPolarCoordinates(const Vec3& normal, float& theta, float& phi)
	{
		theta = std::acos(-normal.y);
		phi = std::atan2(-normal.z, normal.x) + pi;
	}
}