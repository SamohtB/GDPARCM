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
		Metal(const color& a, float f) : albedo(a), fuzz(f < 1 ? f : 1) {}

		bool scatter(const Ray& r_in, const Hit_Record& rec, color& attenuation, Ray& scattered) const override
		{
			auto normalized = r_in.direction;
			normalized.normalize();
			vec3 reflected = reflect(normalized, rec.normal);
			scattered = Ray(rec.p, reflected + random_unit_vector() * fuzz);
			attenuation = albedo;
			return (scattered.direction.dot(rec.normal) > 0);
		}

	private:
		color albedo;
		float fuzz;
	};

	class Dielectric : public Material
	{
	public:
		Dielectric(float index_of_refraction) : ir(index_of_refraction) {}

		bool scatter(const Ray& r_in, const Hit_Record& rec, color& attenuation, Ray& scattered) const override
		{
			attenuation = color(1.0f, 1.0f, 1.0f);
			float refraction_ratio = rec.front_face ? (1.0f / ir) : ir;

			vec3 unit_direction = r_in.direction;
			unit_direction.normalize();
			float cos_theta = fmin(-unit_direction.dot(rec.normal), 1.0f);
			float sin_theta = sqrt(1.0f - cos_theta*cos_theta);

			bool cannot_refract = refraction_ratio * sin_theta > 1.0f;
			vec3 direction;

			if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_float())
				direction = reflect(unit_direction, rec.normal);
			else
				direction = refract(unit_direction, rec.normal, refraction_ratio);

			scattered = Ray(rec.p, direction);
			return true;
		}

	  private:
	    float ir; // Index of Refraction

		static float reflectance(float cosine, float ref_idx)
		{
			// Use Schlick's approximation for reflectance.
			auto r0 = (1 - ref_idx) / (1 + ref_idx);
			r0 = r0 * r0;
			return r0 + (1.f - r0) * pow((1.f - cosine), 5.f);
		}
	};

}

#endif