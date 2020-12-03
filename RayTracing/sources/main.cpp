#include <iostream>
#include <fstream>
#include <cmath>

#include "maths/Vec3.h"
#include "maths/Ray.h"
#include "Random.h"
#include "Camera.h"
#include "hittables/HittableList.h"
#include "hittables/Sphere.h"
#include "materials/Lambertian.h"
#include "materials/Metal.h"

maths::Vec3 Color(const maths::Ray& r, const rt::HittableList& world, size_t depth, size_t depthMax)
{
	rt::HitRecord rec;
	if (world.Hit(r, 0.001f, 1000.f, rec))
	{
		maths::Ray scattered;
		maths::Vec3 attenuation;
		if (depth < depthMax && rec.material->Scatter(r, rec, attenuation, scattered))
			return attenuation * Color(scattered, world, depth + 1, depthMax);
		else
			return maths::Vec3();
	}

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
	const size_t depthMax = 10;

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

	// Camera
	const maths::Vec3 cameraPos;
	const float viewportHeight = 2.f;
	const float focalLength = 1.f;

	const rt::Camera camera(cameraPos, viewportHeight, aspectRatio, focalLength);

	// World initialization
	rt::Hittable** spheres = new rt::Hittable*[4];
	spheres[0] = new rt::Sphere(maths::Vec3(0.f, -500.5f, -1.f), 500.f, new rt::Lambertian(maths::Vec3(0.8f, 0.8f, 0.f)));
	spheres[1] = new rt::Sphere(maths::Vec3(-1.f, 0.f, -1.f), 0.5f, new rt::Metal(maths::Vec3(0.8f, 0.8f, 0.8f)));
	spheres[2] = new rt::Sphere(maths::Vec3(0.f, 0.f, -1.f), 0.5f, new rt::Lambertian(maths::Vec3(0.8f, 0.3f, 0.3f)));
	spheres[3] = new rt::Sphere(maths::Vec3(1.f, 0.f, -1.f), 0.5f, new rt::Metal(maths::Vec3(0.8f, 0.6f, 0.2f)));
	rt::HittableList world(spheres, 4);

	// Render
	for (int j = imageHeight - 1; j >= 0; j--)
	{
		for (int i = 0; i < imageWidth; i++)
		{
			maths::Vec3 color;

			for (size_t s = 0; s < samplesPerPixel; s++)
			{
				float u = (i + rt::Rand01()) / (imageWidth + 1);
				float v = (j + rt::Rand01()) / (imageHeight + 1);
				maths::Ray r = camera.GetRay(u, v);

				color += Color(r, world, 0, depthMax);
			}

			color /= float(samplesPerPixel);
			color.Apply(std::sqrtf);

			out << static_cast<int>(255.999f * color.x) << ' '
				<< static_cast<int>(255.999f * color.y) << ' '
				<< static_cast<int>(255.999f * color.z) << '\n';
		}
	}

	// Closing the output file
	out.close();

	return 0;
}