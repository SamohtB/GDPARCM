#ifndef COLOR_H
#define COLOR_H

#include "Vector3D.h"
#include <iostream>

namespace utility
{
	using color = Vector3D;

	inline void write_color(std::ostream& out, color pixel_color) {
		
		out << static_cast<int>(255.999f * pixel_color.x) << ' '
			<< static_cast<int>(255.999f * pixel_color.y) << ' '
			<< static_cast<int>(255.999f * pixel_color.z) << '\n';
	}
}


#endif