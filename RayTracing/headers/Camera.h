#ifndef RT_CAMERA_H
#define RT_CAMERA_H

#include "maths/Vec3.h"
#include "maths/Ray.h"

namespace rt
{
	class Camera
	{
	public:
		Camera(const maths::Vec3& position, const maths::Vec3& lookAt, const maths::Vec3& up, float verticalFovDeg, float aspectRatio, float aperture, float focusDist, float time0, float time1);

		maths::Vec3 position;
		maths::Vec3 i, j, k;
		maths::Vec3 viewportMinCornerPos;
		maths::Vec3 viewportHorizontal;
		maths::Vec3 viewportVertical;
		float lensRadius;
		float time0, time1;

		maths::Ray GetRay(float u, float v) const;
	};
}

#endif RT_CAMERA_H