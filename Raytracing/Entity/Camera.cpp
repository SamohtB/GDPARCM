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

	center = point3(0, 0, 0);

	auto focal_length = 1.0f;
	auto viewport_height = 2.0f;
	auto viewport_width = viewport_height * (static_cast<float>(image_width) / static_cast<float>(image_height));

	auto viewport_u = vec3(viewport_width, 0, 0);
	auto viewport_v = vec3(0, -viewport_height, 0);

	pixel_delta_u = viewport_u / static_cast<float>(image_width);
	pixel_delta_v = viewport_v / static_cast<float>(image_height);


	auto viewport_upper_left =
		center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
	pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v) * 0.5f;
}

Ray Camera::get_ray(int i, int j) const
{
	auto pixel_center = pixel00_loc + (pixel_delta_u * static_cast<float>(i)) + (pixel_delta_v * static_cast<float>(j));
	auto pixel_sample = pixel_center + pixel_sample_square();

	auto ray_origin = center;
	auto ray_direction = pixel_sample - ray_origin;

	return { ray_origin, ray_direction };
}

vec3 Camera::pixel_sample_square() const
{
	// Returns a random point in the square surrounding a pixel at the origin.
	auto px = -0.5f + random_float();
	auto py = -0.5f + random_float();
	return (pixel_delta_u * px) + (pixel_delta_v * py);
}