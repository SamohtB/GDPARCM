#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "../Raytrace/Hittable.h"
#include "../Utilities/Color.h"
#include "../Utilities/Material.h"
#include "../Raytrace/Raytrace.h"
#include "../Utilities/RTImage.h"

#include <iostream>

namespace entity
{
	using namespace utility;
	using namespace raytrace;

	class Camera {
	public:
		float aspect_ratio = 1.0f;			// Ratio of image width over height
		int   image_width = 512;			// Rendered image width in pixel count
		int   samples_per_pixel = 20;		// Count of random samples for each pixel
		int   max_depth         = 10;   // Maximum number of ray bounces into scene

		float vfov = 90.f;  // Vertical view angle (field of view)
		point3 lookfrom = point3(0, 0, -1);  // Point camera is looking from
		point3 lookat = point3(0, 0, 0);   // Point camera is looking at
		vec3   vup = vec3(0, 1, 0);     // Camera-relative "up" direction

		float defocus_angle = 0.f;  // Variation angle of rays through each pixel
		float focus_dist = 10.f;    // Distance from camera lookfrom point to plane of perfect focus


		void render(const Hittable& world);

	private:
		int    image_height = 0;   // Rendered image height
		point3 center;         // Camera center
		point3 pixel00_loc;    // Location of pixel 0, 0
		vec3   pixel_delta_u;  // Offset to pixel to the right
		vec3   pixel_delta_v;  // Offset to pixel below
		vec3   u, v, w;        // Camera frame basis vectors
		vec3   defocus_disk_u;  // Defocus disk horizontal radius
		vec3   defocus_disk_v;  // Defocus disk vertical radius
		RTImage* image = nullptr;

		void initialize();
		color ray_color(const Ray& r, int depth, const Hittable& world) const;
		point3 defocus_disk_sample() const;
		Ray get_ray(int i, int j) const;
		vec3 pixel_sample_square() const;
	};
}


#endif