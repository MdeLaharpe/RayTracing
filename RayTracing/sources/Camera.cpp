#include "Camera.h"

#include <cmath>

#include "maths/Utils.h"
#include "Random.h"

namespace rt
{
	Camera::Camera(const maths::Vec3& position, const maths::Vec3& lookAt, const maths::Vec3& up, float verticalFovDeg, float aspectRatio, float aperture, float focusDist)
		: position(position), lensRadius(aperture * 0.5f)
	{
		k = maths::Normalized(position - lookAt);
		i = maths::Normalized(maths::Cross(up, k));
		j = maths::Cross(k, i);

		const float viewportHeight = 2.f * focusDist * std::tanf(maths::DegToRad(verticalFovDeg) * 0.5f);
		const float viewportWidth = viewportHeight * aspectRatio;

		viewportHorizontal = viewportWidth * i;
		viewportVertical = viewportHeight * j;
		viewportMinCornerPos = position - viewportHorizontal * 0.5f - viewportVertical * 0.5f - focusDist *  k;
	}

	maths::Ray Camera::GetRay(float u, float v) const
	{
		const maths::Vec3 lens = lensRadius * RandInUnitDisk();
		const maths::Vec3 offset = i * lens.x + j * lens.y;
		const maths::Vec3 rayOrigin = position + offset;
		return maths::Ray(rayOrigin, viewportMinCornerPos + u * viewportHorizontal + v * viewportVertical - rayOrigin);
	}
}