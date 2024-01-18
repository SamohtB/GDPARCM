#pragma once
#ifndef  RAYTRACE_UTIL_H
#define RAYTRACE_UTIL_H

#include <cmath>
#include <limits>
#include <memory>


// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const float infinity = std::numeric_limits<double>::infinity();
const float pi = 3.1415926535897932385f;

// Utility Functions

inline float degrees_to_radians(float degrees)
{
    return degrees * pi / 180.0f;
}

// Common Headers

#include "Ray.h"
#include "../Utilities/Vector3D.h"
#include "../Config/Settings.h"

#endif