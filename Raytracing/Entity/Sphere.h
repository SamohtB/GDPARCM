#ifndef SPHERE_H
#define SPHERE_H

#include "../Raytrace/Hittable.h"
#include "../Utilities/Vector3D.h"

namespace entity
{
	using namespace raytrace;

	class Sphere : public Hittable
	{
	public:
		Sphere(point3 _center, float _radius) : center(_center), radius(_radius) {}
		bool hit(const Ray& r, float ray_tmin, float ray_tmax, Hit_Record& rec) const override;

	private:
		point3 center;
		float radius;
	};
}


#endif