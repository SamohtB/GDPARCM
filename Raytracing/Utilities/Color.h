#ifndef COLOR_H
#define COLOR_H

#include "Vector3D.h"
#include <iostream>

namespace utility
{
	using color = Vector3D;

	inline float linear_to_gamma(float linear_component)
	{
		return sqrt(linear_component);
	}

	inline void write_color(std::ostream& out, color pixel_color, int samples_per_pixel)
	{
		auto r = pixel_color.x;
		auto g = pixel_color.y;
		auto b = pixel_color.z;

		// Divide the color by the number of samples.
		auto scale = 1.0f / static_cast<float>(samples_per_pixel);
		r *= scale;
		g *= scale;
		b *= scale;

		// Apply the linear to gamma transform.
		r = linear_to_gamma(r);
		g = linear_to_gamma(g);
		b = linear_to_gamma(b);

		// Write the translated [0,255] value of each color component.

		static const Interval intensity(0.000f, 0.999f);
		out << static_cast<int>(256 * intensity.clamp(r)) << ' '
			<< static_cast<int>(256 * intensity.clamp(g)) << ' '
			<< static_cast<int>(256 * intensity.clamp(b)) << '\n';
	}

}


#endif
