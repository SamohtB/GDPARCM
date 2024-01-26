#include "Raytrace/Raytrace.h"

#include "Entity/Camera.h"
#include "Utilities/Color.h"
#include "Raytrace/HittableList.h"
#include "Utilities/Material.h"
#include "Entity/Sphere.h"


using namespace utility;
using namespace raytrace;
using namespace entity;


int main()
{
	Hittable_List world;

	auto ground_material = make_shared<Lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<Sphere>(point3(0,-1000,0), 1000, ground_material));

    for (int a = -15; a < 15; a++) {
        for (int b = -15; b < 15; b++) {
            auto choose_mat = random_float();
            point3 center(a + 0.9f * random_float(), 0.2f, b + 0.9f * random_float());

            if ((center - point3(4.f, 0.2f, 0.f)).magnitude() > 0.9f) {
                shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8f) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<Lambertian>(albedo);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95f) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_float(0, 0.5);
                    sphere_material = make_shared<Metal>(albedo, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<Dielectric>(1.5);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5);
    world.add(make_shared<Sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<Lambertian>(color(0.4f, 0.2f, 0.1f));
    world.add(make_shared<Sphere>(point3(-4, 1, 0), 1.0, material2));

	auto material3 = make_shared<Metal>(color(0.7f, 0.6f, 0.5f), 0.0);
    world.add(make_shared<Sphere>(point3(4, 1, 0), 1.0, material3));

    auto material4 = make_shared<Lambertian>(color(0.76f, 0.09f, 0.02f));
    world.add(make_shared<Sphere>(point3(6, 1, 0), 1.0, material4));

    Camera cam;

    cam.aspect_ratio      = 1;
    cam.image_width       = 512;
    cam.samples_per_pixel = 10;
    cam.max_depth         = 10;

    cam.vfov     = 20;
    cam.lookfrom = point3(13,2,3);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0.6f;
    cam.focus_dist    = 10.0;

    cam.render(world);
}