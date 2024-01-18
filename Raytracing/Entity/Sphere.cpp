#include "Sphere.h"

using namespace entity;

bool Sphere::hit(const Ray& r, float ray_tmin, float ray_tmax, Hit_Record& rec) const override
{
	vec3 oc = r.origin - center;
	auto a = r.direction.magnitudeSquared();
	auto half_b = oc.dot(r.direction);
	auto c = oc.magnitudeSquared() - radius * radius;

	auto discriminant = half_b * half_b - a * c;
	if (discriminant < 0) { return false; }
	auto sqrtd = sqrt(discriminant);

	auto root = (-half_b - sqrtd) / a;
	if (root <= ray_tmin || ray_tmax <= root) 
	{
		root = (-half_b + sqrtd) / a;
		if (root <= ray_tmin || ray_tmax <= root)
		{
			return false;
		}
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	vec3 outward_normal = (rec.p - center) / radius;
	rec.set_face_normal(r, outward_normal);

	return true;
}