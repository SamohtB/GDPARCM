#include "Raytrace/Raytrace.h"

#include "Utilities/Color.h"
#include "Raytrace/Hittable.h"
#include "Raytrace/HittableList.h"
#include "Entity/Sphere.h"

#include <iostream>

using namespace utility;
using namespace raytrace;
using namespace entity;

color ray_color(const Ray& r, const Hittable& world)
{
    Hit_Record rec;
    if (world.hit(r, 0, infinity, rec)) 
	{
        return (rec.normal + color(1,1,1)) * 0.5f;
    }

	vec3 unit_direction = r.direction;
	unit_direction.normalize();
    float a = 0.5f * (unit_direction.y + 1.0f);
    return color(1.0f, 1.0f, 1.0f)* (1.0f - a)+ color(0.5f, 0.7f, 1.0f) * a;
}


int main() {

	// Image
	float aspect_ratio = ASPECT_RATIO_WIDTH / ASPECT_RATION_HEIGHT;
	int image_width = IMAGE_WIDTH;

	// Calculate the image height, and ensure that it's at least 1.
	int image_height = static_cast<int>(image_width / aspect_ratio);
	image_height = (image_height < 1) ? 1 : image_height;

	 // World
    Hittable_List world;

    world.add(make_shared<Sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<Sphere>(point3(0,-100.5,-1), 100));

	// Camera
	float focal_length = 1.0;
	float viewport_height = 2.0;
	float viewport_width = viewport_height * (static_cast<float>(image_width) / image_height);
	point3 camera_center = point3(0, 0, 0);

	// Calculate the vectors across the horizontal and down the vertical viewport edges.
	vec3 viewport_u = vec3(viewport_width, 0, 0);
	vec3 viewport_v = vec3(0, -viewport_height, 0);

	// Calculate the horizontal and vertical delta vectors from pixel to pixel.
	vec3 pixel_delta_u = viewport_u / image_width;
	vec3 pixel_delta_v = viewport_v / image_height;

	// Calculate the location of the upper left pixel.
	vec3 viewport_upper_left = camera_center
		- vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
	vec3 pixel00_loc = viewport_upper_left +(pixel_delta_u + pixel_delta_v) *  0.5f;

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) 
    {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) 
        {
            auto pixel_center = pixel00_loc + (pixel_delta_u * i) + (pixel_delta_v * j);
            auto ray_direction = pixel_center - camera_center;
            Ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";
}