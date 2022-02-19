#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#include "maths/Vec3.h"
#include "maths/Ray.h"
#include "Random.h"
#include "Camera.h"
#include "hittables/BVHNode.h"
#include "hittables/HittableList.h"
#include "hittables/Sphere.h"
#include "hittables/MovingSphere.h"
#include "materials/Lambertian.h"
#include "materials/Metal.h"
#include "materials/Dielectric.h"
#include "materials/DiffuseLight.h"
#include "textures/SolidColorTexture.h"
#include "textures/CheckerTexture.h"
#include "textures/NoiseTexture.h"
#include "textures/ImageTexture.h"

maths::Vec3 Color(const maths::Ray& r, const maths::Vec3& backgroundColor, const rt::Hittable& world, size_t depth, size_t depthMax)
{
	rt::HitRecord rec;
	if (world.Hit(r, 0.001f, 1000.f, rec))
	{
		maths::Ray scattered;
		maths::Vec3 attenuation;
		maths::Vec3 emitted = rec.material->Emit(rec.u, rec.v, rec.point);

		if (depth < depthMax && rec.material->Scatter(r, rec, attenuation, scattered))
			return emitted + attenuation * Color(scattered, backgroundColor, world, depth + 1, depthMax);
		else
			return emitted;
	}

	return backgroundColor;
}

int main(int argc, char* argv[])
{
	const std::string outputFileName{ "out.ppm" };

	// Image
	const float aspectRatio = 16.f / 9.f;
	const size_t imageWidth = 800;
	const size_t imageHeight = static_cast<int>(imageWidth / aspectRatio);
	const size_t samplesPerPixel = 100;
	const size_t depthMax = 5;

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
	const float time0 =  0.f, time1 = 1.f;
	const maths::Vec3 cameraPos{ 5.f, 2.f, 1.f };
	const maths::Vec3 lookAt{ 0.f, 1.f, -3.f };
	const maths::Vec3 up{ 0.f, 1.f, 0.f };
	const float verticalFovDeg = 90.f;
	const float aperture = 0.01f;
	const float focusDist = (cameraPos - lookAt).Magnitude();

	const rt::Camera camera(cameraPos, lookAt, up, verticalFovDeg, aspectRatio, aperture, focusDist, time0, time1);

	// World initialization
	std::vector<std::shared_ptr<rt::Hittable>> spheres;
	spheres.reserve(5);

	std::shared_ptr<rt::Texture> oddEvenTexture = std::make_shared<rt::SolidColorTexture>(maths::Vec3(0.8f, 0.8f, 0.f));
	std::shared_ptr<rt::Texture> oddOddTexture = std::make_shared<rt::SolidColorTexture>(maths::Vec3(0.f, 0.f, 0.f));
	std::shared_ptr<rt::Texture> noiseTexture = std::make_shared<rt::NoiseTexture>(5.f, 7, rt::NoiseTexture::CastMethod::Abs);
	spheres.emplace_back(new rt::Sphere(maths::Vec3(0.f, -500.5f, -1.f), 500.f, std::make_shared<rt::Lambertian>(noiseTexture)));

	spheres.emplace_back(new rt::Sphere(maths::Vec3(-1.f, 0.f, -1.f), 0.5f, std::make_shared<rt::Dielectric>(1.5f)));
	spheres.emplace_back(new rt::Sphere(maths::Vec3(-1.f, 0.f, -1.f), -0.45f, std::make_shared<rt::Dielectric>(1.5f)));
	spheres.emplace_back(new rt::MovingSphere(maths::Vec3(0.f, 0.f, -1.f), maths::Vec3(0.f, 1.f, -1.f), time0, time1, 0.5f, std::make_shared<rt::Lambertian>(maths::Vec3(0.8f, 0.3f, 0.3f))));
	//spheres.emplace_back(new rt::Sphere(maths::Vec3(1.f, 0.f, -1.f), 0.5f, std::make_shared<rt::Metal>(maths::Vec3(0.8f, 0.6f, 0.2f), 1.f)));
	spheres.emplace_back(new rt::Sphere(maths::Vec3(2.f, 4.f, -3.f), 0.5f, std::make_shared<rt::DiffuseLight>()));

	std::shared_ptr<rt::Texture> earthTexture = std::make_shared<rt::ImageTexture>("resources/earthmap.jpg");
	spheres.emplace_back(new rt::Sphere(maths::Vec3(0.f, 1.f, -3.f), 2.f, std::make_shared<rt::Lambertian>(earthTexture)));

	const rt::BVHNode world(spheres, 0, spheres.size(), time0, time1);

	const maths::Vec3 backgroundColor{ 0.0f, 0.0f, 0.f };

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

				color += Color(r, backgroundColor, world, 0, depthMax);
			}

			color /= float(samplesPerPixel);
			color.Apply(std::sqrtf);

			out << static_cast<int>(255.999f * color.r) << ' '
				<< static_cast<int>(255.999f * color.g) << ' '
				<< static_cast<int>(255.999f * color.b) << '\n';
		}
	}

	// Closing the output file
	out.close();

	return 0;
}