#include "HittableList.h"

using namespace raytrace;

bool Hittable_List::hit(const Ray& r, float ray_tmin, float ray_tmax, Hit_Record& rec) const
{
	Hit_Record temp_rec;
	bool hit_anything = false;
	auto closest_so_far = ray_tmax;

	for (const auto& object : objects) 
	{
		if (object->hit(r, ray_tmin, closest_so_far, temp_rec)) 
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}

	return hit_anything;
}

void Hittable_List::clear()
{
	objects.clear(); 
}

void Hittable_List::add(const shared_ptr<Hittable>& object)
{
	objects.push_back(object);
}
