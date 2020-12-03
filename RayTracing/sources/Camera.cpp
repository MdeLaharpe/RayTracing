#include "Camera.h"

namespace rt
{
	Camera::Camera(const maths::Vec3& position, float viewportHeight, float aspectRatio, float focalLength)
		: position(position)
	{
		const float viewportWidth = viewportHeight * aspectRatio;
		viewportHorizontal = maths::Vec3(viewportWidth, 0.f, 0.f);
		viewportVertical = maths::Vec3(0.f, viewportHeight, 0.f);
		viewportMinCornerPos = position - viewportHorizontal * 0.5f - viewportVertical * 0.5f - maths::Vec3(0.f, 0.f, focalLength);
	}

	maths::Ray Camera::GetRay(float u, float v) const
	{
		return maths::Ray(position, viewportMinCornerPos + u * viewportHorizontal + v * viewportVertical - position);
	}
}