#include "Camera.h"

using namespace entity;

void Camera::render(const Hittable& world)
{
	initialize();

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = 0; j < image_height; ++j) 
	{
		std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;

		for (int i = 0; i < image_width; ++i) 
		{
			color pixel_color(0, 0, 0);
			for (int sample = 0; sample < samples_per_pixel; ++sample) {
				Ray r = get_ray(i, j);
				pixel_color += ray_color(r, max_depth, world);
			}
			write_color(std::cout, pixel_color, samples_per_pixel);
		}
	}

	std::clog << "\rDone.                 \n";
}

color Camera::ray_color(const Ray& r, int depth, const Hittable& world) const
{
	Hit_Record rec;

	if (depth <= 0) { return color(0,0,0); }

	if (world.hit(r, Interval(0.001f, infinity), rec))
	{
		Ray scattered;
		color attenuation;

		if (rec.mat->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * ray_color(scattered, depth-1, world);
		}
                
		return color(0,0,0);
	}

	vec3 unit_direction = r.direction;
	unit_direction.normalize();
	auto a = (unit_direction.y + 1.0f) * 0.5f;
	return color(1.0f, 1.0f, 1.0f) * (1.0f - a) + color(0.5f, 0.7f, 1.0f) * a;
}

void Camera::initialize()
{
	image_height = image_width / static_cast<int>(aspect_ratio);
	image_height = image_height < 1 ? 1 : image_height;

	center = lookfrom;

	auto theta = degrees_to_radians(vfov);
    auto h = tan(theta/2);
	auto viewport_height = 2 * h * focus_dist;
	auto viewport_width = viewport_height * (static_cast<float>(image_width) / static_cast<float>(image_height));

	// Calculate the u,v,w unit basis vectors for the camera coordinate frame.
	w = lookfrom - lookat;
	w.normalize();
	u = vup.cross(w);
	u.normalize();
	v = w.cross(u);

	vec3 viewport_u = u * viewport_width;    // Vector across viewport horizontal edge
	vec3 viewport_v = -v * viewport_height;  // Vector down viewport vertical edge

	pixel_delta_u = viewport_u / static_cast<float>(image_width);
	pixel_delta_v = viewport_v / static_cast<float>(image_height);


	auto viewport_upper_left =
		center - (w * focus_dist) - viewport_u / 2 - viewport_v / 2;
	pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v) * 0.5f;

	auto defocus_radius = focus_dist * tan(degrees_to_radians(defocus_angle / 2));
	defocus_disk_u = u * defocus_radius;
	defocus_disk_v = v * defocus_radius;
}

Ray Camera::get_ray(int i, int j) const
{
	// Get a randomly-sampled camera ray for the pixel at location i,j, originating from
        // the camera defocus disk.

	auto pixel_center = pixel00_loc + (pixel_delta_u * static_cast<float>(i)) + (pixel_delta_v * static_cast<float>(j));
	auto pixel_sample = pixel_center + pixel_sample_square();

	auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
	auto ray_direction = pixel_sample - ray_origin;

	return { ray_origin, ray_direction };
}


point3 Camera::defocus_disk_sample() const
{
	// Returns a random point in the camera defocus disk.
	auto p = random_in_unit_disk();
	return center + (defocus_disk_u * p[0]) + (defocus_disk_v * p[1]);
}

vec3 Camera::pixel_sample_square() const
{
	// Returns a random point in the square surrounding a pixel at the origin.
	auto px = -0.5f + random_float();
	auto py = -0.5f + random_float();
	return (pixel_delta_u * px) + (pixel_delta_v * py);
}