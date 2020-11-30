#ifndef MATHS_VEC3_H
#define MATHS_VEC3_H

#include <cmath>
#include <ostream>

namespace maths
{
	struct Vec3
	{
		constexpr Vec3() : val{ 0.f, 0.f, 0.f } {};
		constexpr Vec3(float x, float y, float z) : val{ x, y, z } {};

		Vec3(const Vec3& v) = default;
		Vec3(Vec3&& v) = default;

		~Vec3() = default;

		union
		{
			struct { float x, y, z; };
			struct { float r, g, b; };
			float val[3];
		};

		inline float operator[](size_t i) const { return val[i]; }
		inline float& operator[](size_t i) { return val[i]; }

		inline Vec3 operator -() const
		{
			return Vec3(-x, -y, -z);
		}

		inline Vec3& operator *=(const float f)
		{
			x *= f;
			y *= f;
			z *= f;

			return *this;
		}
		inline Vec3& operator /=(const float f)
		{
			*this *= (1.f / f);

			return *this;
		}

		inline Vec3& operator +=(const Vec3& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;

			return *this;
		}
		inline Vec3& operator -=(const Vec3& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;

			return *this;
		}
	};

	inline Vec3 operator *(const Vec3& v, const float f)
	{
		return Vec3(v.x * f, v.y * f, v.z * f);
	}
	inline Vec3 operator *(const float f, const Vec3& v)
	{
		return v * f;
	}
	inline Vec3 operator /(const Vec3& v, const float f)
	{
		return v * (1.f / f);
	}

	inline Vec3 operator +(const Vec3& l, const Vec3& r)
	{
		return Vec3(l.x + r.x, l.y + r.y, l.z + r.z);
	}
	inline Vec3 operator -(const Vec3& l, const Vec3& r)
	{
		return Vec3(l.x - r.x, l.y - r.y, l.z - r.z);
	}
	inline Vec3 operator *(const Vec3& l, const Vec3& r)
	{
		return Vec3(l.x * r.x, l.y * r.y, l.z * r.z);
	}
	inline Vec3 operator /(const Vec3& l, const Vec3& r)
	{
		return Vec3(l.x / r.x, l.y / r.y, l.z / r.z);
	}

	inline float magnitude_squared(const Vec3& v)
	{
		return v.x * v.x + v.y * v.y + v.z * v.z;
	}
	inline float magnitude(const Vec3& v)
	{
		return std::sqrtf(magnitude_squared(v));
	}

	inline Vec3 normalized(const Vec3& v)
	{
		return v * (1.f / magnitude(v));
	}
	inline float dot(const Vec3& l, const Vec3& r)
	{
		return l.x * r.x + l.y * r.y + l.z * r.z;
	}
	inline Vec3 cross(const Vec3& l, const Vec3& r)
	{
		return Vec3(
			l.y * r.z - l.z * r.y,
			l.z * r.x - l.x * r.z,
			l.x * r.y - l.y * r.x
		);
	}

	std::ostream& operator<<(std::ostream& out, const Vec3& v)
	{
		return out << v.x << ' ' << v.y << ' ' << v.z;
	}
}

#endif