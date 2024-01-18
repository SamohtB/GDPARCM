#pragma once
#ifndef VECTOR_3D_H
#define VECTOR_3D_H

#include <iostream>
#include <cmath>

namespace utility
{
	class Vector3D
	{
	public:
		Vector3D();
		Vector3D(float x, float y, float z);
		~Vector3D() = default;

		Vector3D operator+(Vector3D vectorB) const;
		Vector3D& operator+=(Vector3D vectorB);
		Vector3D operator-(Vector3D vectorB) const;
		Vector3D& operator-=(Vector3D vectorB);
		Vector3D operator*(float scalar) const;
		Vector3D& operator*=(float scalar);
		Vector3D operator*(Vector3D vectorB) const;
		Vector3D operator/(float scalar);
		Vector3D& operator/=(float scalar);
		Vector3D operator-()const;
		float operator[](int i) const;
		float& operator[](int i);
		friend std::ostream& operator<<(std::ostream& os, const Vector3D& vector);

		void zero();
		float dot(Vector3D vectorB);
		Vector3D cross(Vector3D vectorB);

		void normalize();
		float magnitude() const;
		float magnitudeSquared() const;

		float x;
		float y;
		float z;
	};
}

#endif





