#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.h"
#include "../Raytrace/Hittable.h"
#include "../Raytrace/Raytrace.h"

namespace raytrace
{
	class Ray;
	class Hit_Record;
}

namespace utility
{
	using namespace raytrace;

	class Material
	{
	public:
		virtual ~Material() = default;

		virtual bool scatter(
			const Ray& r_in, const Hit_Record& rec, color& attenuation, Ray& scattered) const = 0;
	};

	class Lambertian : public Material
	{
	public:
		Lambertian(const color& a) : albedo(a) {}

		bool scatter(const Ray& r_in, const Hit_Record& rec, color& attenuation, Ray& scattered) const override
		{
			auto scatter_direction = rec.normal + random_unit_vector();

			// Catch degenerate scatter direction
			if (scatter_direction.near_zero())
				scatter_direction = rec.normal;

			scattered = Ray(rec.p, scatter_direction);
			attenuation = albedo;
			return true;
		}

	private:
		color albedo;
	};

	class Metal : public Material
	{
	public:
		Metal(const color& a) : albedo(a) {}

		bool scatter(const Ray& r_in, const Hit_Record& rec, color& attenuation, Ray& scattered) const override
		{
			auto normalized = r_in.direction;
			normalized.normalize();
			vec3 reflected = reflect(normalized, rec.normal);
			scattered = Ray(rec.p, reflected);
			attenuation = albedo;
			return true;
		}

	private:
		color albedo;
	};

}

#endif