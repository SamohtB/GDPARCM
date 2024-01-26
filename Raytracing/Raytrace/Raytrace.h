#pragma once
#ifndef RAYTRACE_UTIL_H
#define RAYTRACE_UTIL_H

#include <cmath>
#include <cstdlib>
#include <random>
#include <limits>
#include <memory>


// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.1415926535897932385f;

// Utility Functions

inline float degrees_to_radians(float degrees)
{
    return degrees * pi / 180.0f;
}

inline float random_float()
{
    static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    static std::mt19937 generator;
    return distribution(generator);
}

inline float random_float(float min, float max)
{
    static std::uniform_real_distribution<float> distribution(min, max);
    static std::mt19937 generator;
    return distribution(generator);
}

// Common Headers

#include "../Utilities/Vector3D.h"
#include "../Utilities/Interval.h"
#include "../Config/Settings.h"


#endif