#ifndef RT_CAMERA_H
#define RT_CAMERA_H

#include "maths/Vec3.h"
#include "maths/Ray.h"

namespace rt
{
	class Camera
	{
	public:
		Camera() : Camera({}, { 0.f, 0.f, -1.f }, { 0.f, 1.f, 0.f }, 90.f, 16.f / 9.f, 0.2f, 10.f) { }
		Camera(const maths::Vec3& position, const maths::Vec3& lookAt, const maths::Vec3& up, float verticalFovDeg, float aspectRatio, float aperture, float focusDist);

		maths::Vec3 position;
		maths::Vec3 i, j, k;
		maths::Vec3 viewportMinCornerPos;
		maths::Vec3 viewportHorizontal;
		maths::Vec3 viewportVertical;
		float lensRadius;

		maths::Ray GetRay(float u, float v) const;
	};
}

#endif RT_CAMERA_H