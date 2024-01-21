#include "Raytrace/Raytrace.h"

#include "Raytrace/HittableList.h"
#include "Entity/Sphere.h"
#include "Entity/Camera.h"

using namespace utility;
using namespace raytrace;
using namespace entity;


int main()
{
	Hittable_List world;

    world.add(make_shared<Sphere>(point3(0,0,-1), 0.5f));
    world.add(make_shared<Sphere>(point3(0,-100.5f,-1), 100.f));

    Camera cam;

    cam.aspect_ratio = 16.0f / 9.0f;
    cam.image_width  = 400;

    cam.render(world);
}