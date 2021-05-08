#ifndef RT_CAMERA_H
#define RT_CAMERA_H

#include "maths/Vec3.h"
#include "maths/Ray.h"

namespace rt
{
	class Camera
	{
	public:
		Camera() : Camera({}, { 0.f, 0.f, -1.f }, { 0.f, 1.f, 0.f }, 2.f, 16.f / 9.f, 1.f) { }
		Camera(const maths::Vec3& position, const maths::Vec3& lookAt, const maths::Vec3& up, float verticalFovDeg, float aspectRatio, float focalLength);

		maths::Vec3 position;
		maths::Vec3 viewportMinCornerPos;
		maths::Vec3 viewportHorizontal;
		maths::Vec3 viewportVertical;

		maths::Ray GetRay(float u, float v) const;
	};
}

#endif RT_CAMERA_H