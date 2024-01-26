#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "../Raytrace/Hittable.h"
#include "../Utilities/Color.h"
#include "../Utilities/Material.h"
#include "../Raytrace/Raytrace.h"

#include <iostream>

namespace entity
{
	using namespace utility;
	using namespace raytrace;

	class Camera {
	public:
		float aspect_ratio = 1.0f;			// Ratio of image width over height
		int   image_width = 100;			// Rendered image width in pixel count
		int   samples_per_pixel = 10;		// Count of random samples for each pixel
		int   max_depth         = 10;   // Maximum number of ray bounces into scene

		void render(const Hittable& world);

	private:
		int    image_height = 0;   // Rendered image height
		point3 center;         // Camera center
		point3 pixel00_loc;    // Location of pixel 0, 0
		vec3   pixel_delta_u;  // Offset to pixel to the right
		vec3   pixel_delta_v;  // Offset to pixel below

		void initialize();
		color ray_color(const Ray& r, int depth, const Hittable& world) const;
		Ray get_ray(int i, int j) const;
		vec3 pixel_sample_square() const;
	};
}


#endif