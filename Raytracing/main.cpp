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

	auto material_ground = make_shared<Lambertian>(color(0.8f, 0.8f, 0.0));
    auto material_center = make_shared<Lambertian>(color(0.7f, 0.3f, 0.3f));
    auto material_left   = make_shared<Metal>(color(0.8f, 0.8f, 0.8f));
    auto material_right  = make_shared<Metal>(color(0.8f, 0.6f, 0.2f));

    world.add(make_shared<Sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<Sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center));
    world.add(make_shared<Sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<Sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));

    Camera cam;

    cam.aspect_ratio = 16.0f / 9.0f;
    cam.image_width  = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    cam.render(world);
}