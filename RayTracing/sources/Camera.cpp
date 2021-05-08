#include "Camera.h"

#include <cmath>

#include "maths/Utils.h"

namespace rt
{
	Camera::Camera(const maths::Vec3& position, const maths::Vec3& lookAt, const maths::Vec3& up, float verticalFovDeg, float aspectRatio, float focalLength)
		: position(position)
	{
		const float viewportHeight = 2.f * focalLength * std::tanf(maths::DegToRad(verticalFovDeg) * 0.5f);
		const float viewportWidth = viewportHeight * aspectRatio;

		const maths::Vec3 w = maths::Normalized(position - lookAt);
		const maths::Vec3 u = maths::Normalized(maths::Cross(up, w));
		const maths::Vec3 v = maths::Cross(w, u);

		viewportHorizontal = viewportWidth * u;
		viewportVertical = viewportHeight * v;
		viewportMinCornerPos = position - viewportHorizontal * 0.5f - viewportVertical * 0.5f - focalLength * w;
	}

	maths::Ray Camera::GetRay(float u, float v) const
	{
		return maths::Ray(position, viewportMinCornerPos + u * viewportHorizontal + v * viewportVertical - position);
	}
}