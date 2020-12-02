#include <iostream>
#include <fstream>
#include <cmath>

#include "maths/Vec3.h"
#include "maths/Ray.h"
#include "hittables/Sphere.h"

bool hit_sphere(const maths::Vec3& center, float radius, const maths::Ray& r, float& hitTime)
{
	maths::Vec3 oc = r.origin - center;
	float a = r.direction.magnitude_squared();
	float halfB = maths::dot(oc, r.direction);
	float c = oc.magnitude_squared() - radius * radius;
	float discriminant = halfB * halfB - a * c;

	if (discriminant < 0.f)
		return false;
	else
	{
		hitTime = (-halfB - sqrtf(discriminant)) / a;
		return true;
	}
}

maths::Vec3 ray_color(const maths::Ray& r)
{
	const rt::Sphere sphere(maths::Vec3(0.f, 0.f, -1.f), 0.5f);
	rt::HitRecord rec;
	if (sphere.hit(r, 0.f, 1000.f, rec))
		return 0.5f * maths::Vec3(rec.normal.x + 1.f, rec.normal.y + 1.f, rec.normal.z + 1.f);

	maths::Vec3 unitDirection = normalized(r.direction);
	float t = 0.5f * (unitDirection.y + 1.f);
	return (1.f - t) * maths::Vec3(1.f, 1.f, 1.f) + t * maths::Vec3(0.5f, 0.7f, 1.f);
}

int main(int argc, char* argv[])
{
	const char* outputFileName = "out.ppm";

	// Image
	const float aspectRatio = 16.f / 9.f;
	const int imageWidth = 400;
	const int imageHeight = static_cast<int>(imageWidth / aspectRatio);

	// Camera
	const float viewportHeight = 2.f;
	const float viewportWidth = viewportHeight * aspectRatio;
	const float focalLength = 1.f;

	const maths::Vec3 eyePos = maths::Vec3();
	const maths::Vec3 horizontal = maths::Vec3(viewportWidth, 0.f, 0.f);
	const maths::Vec3 vertical = maths::Vec3(0.f, viewportHeight, 0.f);
	const maths::Vec3 lowerLeftCorner = eyePos - horizontal / 2.f - vertical / 2.f - maths::Vec3(0.f, 0.f, focalLength);

	// Opening the output file
	std::ofstream out;
	out.open(outputFileName, std::ios_base::out | std::ios_base::trunc);
	if (!out.is_open())
	{
		std::cerr << "Could not open file " << outputFileName << " for writing" << std::endl;
		return -1;
	}

	// PPM image format header
	out << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

	// Render
	for (int j = imageHeight - 1; j >= 0; j--)
	{
		for (int i = 0; i < imageWidth; i++)
		{
			float u = float(i) / (imageWidth + 1);
			float v = float(j) / (imageHeight + 1);
			maths::Ray r(eyePos, lowerLeftCorner + u * horizontal + v * vertical - eyePos);

			maths::Vec3 color = ray_color(r);

			out << static_cast<int>(255.999f * color.x) << ' '
				<< static_cast<int>(255.999f * color.y) << ' '
				<< static_cast<int>(255.999f * color.z) << '\n';
		}
	}

	// Closing the output file
	out.close();

	return 0;
}