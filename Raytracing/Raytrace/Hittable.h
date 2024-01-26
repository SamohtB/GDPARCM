#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"
#include "Raytrace.h"


namespace utility
{
	class Material;
}

namespace raytrace
{
	class Hit_Record
	{
	public:
		point3 p;
		vec3 normal;
		shared_ptr<Material> mat;
		float t;
		bool front_face;

		void set_face_normal(const Ray& r, const vec3& outward_normal)
		{
			front_face = r.direction.dot(outward_normal) < 0;
			normal = front_face ? outward_normal : -outward_normal;
		}
	};

	class Hittable
	{
	public:
		virtual ~Hittable() = default;
		virtual bool hit(const Ray& r, Interval ray_t, Hit_Record& rec) const = 0;

	};
}

#endif