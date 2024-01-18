#pragma once
#ifndef RAY_H
#define RAY_H

#include "../Utilities/Vector3D.h"

namespace raytrace
{
	using namespace utility;

	class Ray
	{
	public:
		Ray() = default;
		Ray(const point3& origin, const vec3& direction) : origin(origin), direction(direction) {}
		point3 at(float t) const { return origin + direction * t; }
		point3 origin;
		vec3 direction;
	};
}


#endif