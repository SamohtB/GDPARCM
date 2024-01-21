#pragma once
#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "Hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

namespace raytrace
{
	class Hittable_List : public Hittable {
	public:
		std::vector<shared_ptr<Hittable>> objects;

		Hittable_List() = default;
		Hittable_List(const shared_ptr<Hittable>& object) { add(object); }

		void clear();
		void add(const shared_ptr<Hittable>& object);
		bool hit(const Ray& r, Interval ray_t, Hit_Record& rec) const override;
	};
}

#endif
