#pragma once
#ifndef VECTOR_3D_H
#define VECTOR_3D_H

#include <iostream>
#include <cmath>

#include "../Raytrace/Raytrace.h"

namespace utility
{
	class Vector3D
	{
	public:
		Vector3D();
		Vector3D(float x, float y, float z);
		using vec3 = Vector3D;

		Vector3D operator+(Vector3D vectorB) const;
		Vector3D& operator+=(Vector3D vectorB);
		Vector3D operator-(Vector3D vectorB) const;
		Vector3D& operator-=(Vector3D vectorB);
		Vector3D operator*(const Vector3D& vectorB) const;
		Vector3D operator*(float scalar) const;
		Vector3D& operator*=(float scalar);
		Vector3D operator/(float scalar) const;
		Vector3D& operator/=(float scalar);
		Vector3D operator-() const;
		float operator[](int i) const;
		float& operator[](int i);
		friend std::ostream& operator<<(std::ostream& os, const Vector3D& vector);

		void zero();
		float dot(const Vector3D& vectorB) const;
		Vector3D cross(const Vector3D& vectorB) const;

		void normalize();
		float magnitude() const;
		float magnitudeSquared() const;
		bool near_zero() const;
		

		static vec3 random();
		static vec3 random(float min, float max);

		float x;
		float y;
		float z;
	};

	inline Vector3D random_in_unit_sphere()
	{
		while (true)
		{
			auto p = Vector3D::random(-1, 1);
			if (p.magnitudeSquared() < 1)
				return p;
		}
	}

	inline Vector3D random_unit_vector()
	{
		Vector3D a = random_in_unit_sphere();
		a.normalize();
		return a;
	}

	inline Vector3D random_on_hemisphere(const Vector3D& normal)
	{
		Vector3D on_unit_sphere = random_unit_vector();
		if (on_unit_sphere.dot(normal) > 0.0f) // In the same hemisphere as the normal
			return on_unit_sphere;
		else
			return -on_unit_sphere;
	}

	inline Vector3D reflect(const Vector3D& v, const Vector3D& n)
	{
		return v - n * 2.f * v.dot(n);
	}

	inline Vector3D refract(const Vector3D& uv, const Vector3D& n, float etai_over_etat)
	{
		auto cos_theta = fmin(-uv.dot(n), 1.0f);
		Vector3D r_out_perp =  (n * cos_theta + uv) * etai_over_etat;
		Vector3D r_out_parallel = n * -sqrt(fabs(1.0f - r_out_perp.magnitudeSquared()));
		return r_out_perp + r_out_parallel;
	}

	inline Vector3D random_in_unit_disk()
	{
		while (true) 
		{
			auto p = Vector3D(random_float(-1.f, 1.f), random_float(-1.f, 1.f), 0.f);
			if (p.magnitudeSquared() < 1)
				return p;
		}
	}

	inline float clamp(float value, float min, float max)
	{
		if(value < min)
		{
			return min;
		}

		if(value > max)
		{
			return max;
		}

		return value;
	}

	typedef Vector3D vec3;
	typedef Vector3D point3;
}



typedef utility::Vector3D vec3;

#endif
