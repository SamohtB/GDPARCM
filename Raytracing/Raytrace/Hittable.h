#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"

namespace raytrace
{
	class Hit_Record
	{
	public:
		point3 p;
		vec3 normal;
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
		virtual bool hit(const Ray& r, float ray_tmin, float ray_tmax, Hit_Record& rec) const = 0;
	};
}

#endif