#include <iostream>
#include <fstream>
#include <cmath>

#include "maths/Vec3.h"
#include "maths/Ray.h"
#include "Random.h"
#include "Camera.h"
#include "hittables/HittableList.h"
#include "hittables/Sphere.h"

maths::Vec3 Color(const maths::Ray& r, const rt::HittableList& world)
{
	rt::HitRecord rec;
	if (world.Hit(r, 0.f, 1000.f, rec))
		return 0.5f * maths::Vec3(rec.normal.x + 1.f, rec.normal.y + 1.f, rec.normal.z + 1.f);

	maths::Vec3 unitDirection = Normalized(r.direction);
	float t = 0.5f * (unitDirection.y + 1.f);
	return (1.f - t) * maths::Vec3(1.f, 1.f, 1.f) + t * maths::Vec3(0.5f, 0.7f, 1.f);
}

int main(int argc, char* argv[])
{
	const char* outputFileName = "out.ppm";

	// Image
	const float aspectRatio = 16.f / 9.f;
	const size_t imageWidth = 400;
	const size_t imageHeight = static_cast<int>(imageWidth / aspectRatio);
	const size_t samplesPerPixel = 16;

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

	// RNG initialization
	rt::Random random;

	// Camera
	const maths::Vec3 cameraPos;
	const float viewportHeight = 2.f;
	const float focalLength = 1.f;

	const rt::Camera camera(cameraPos, viewportHeight, aspectRatio, focalLength);

	// World initialization
	rt::Hittable* spheres[4];
	spheres[0] = new rt::Sphere(maths::Vec3(0.f, -500.5f, -1.f), 500.f);
	spheres[1] = new rt::Sphere(maths::Vec3(-1.f, 0.f, -1.f), 0.5f);
	spheres[2] = new rt::Sphere(maths::Vec3(0.f, 0.f, -1.f), 0.5f);
	spheres[3] = new rt::Sphere(maths::Vec3(1.f, 0.f, -1.f), 0.5f);
	rt::HittableList world(spheres, 4);

	// Render
	for (int j = imageHeight - 1; j >= 0; j--)
	{
		for (int i = 0; i < imageWidth; i++)
		{
			maths::Vec3 color;

			for (size_t s = 0; s < samplesPerPixel; s++)
			{
				float u = (i + random.Rand01()) / (imageWidth + 1);
				float v = (j + random.Rand01()) / (imageHeight + 1);
				maths::Ray r = camera.GetRay(u, v);

				color += Color(r, world);
			}

			color /= float(samplesPerPixel);
			color.Apply(std::sqrtf);

			out << static_cast<int>(255.999f * color.x) << ' '
				<< static_cast<int>(255.999f * color.y) << ' '
				<< static_cast<int>(255.999f * color.z) << '\n';
		}
	}

	// World de-initialization
	delete spheres[0];
	delete spheres[1];
	delete spheres[2];

	// Closing the output file
	out.close();

	return 0;
}