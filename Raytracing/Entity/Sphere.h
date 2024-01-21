#ifndef SPHERE_H
#define SPHERE_H

#include "../Raytrace/Hittable.h"

namespace entity
{
	using namespace raytrace;

	class Sphere : public Hittable
	{
	public:
		Sphere(point3 _center, float _radius) : center(_center), radius(_radius) {}
		bool hit(const Ray& r, Interval ray_t, Hit_Record& rec) const override;

	private:
		point3 center;
		float radius;
	};
}


#endif