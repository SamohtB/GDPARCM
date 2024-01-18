#include "Vector3D.h"

using namespace utility;

Vector3D::Vector3D()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

Vector3D::Vector3D(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3D Vector3D::operator+(Vector3D vectorB) const
{
    return {this->x + vectorB.x, this->y + vectorB.y, this->z + vectorB.z};
}

Vector3D& Vector3D::operator+=(Vector3D vectorB)
{
    this->x += vectorB.x;
    this->y += vectorB.y;
    this->z += vectorB.z;

    return *this;
}

Vector3D Vector3D::operator-(Vector3D vectorB) const
{
    return {this->x - vectorB.x, this->y - vectorB.y, this->z - vectorB.z};
}

Vector3D& Vector3D::operator-=(Vector3D vectorB)
{
    this->x -= vectorB.x;
    this->y -= vectorB.y;
    this->z -= vectorB.z;

    return *this;
}

Vector3D Vector3D::operator*(float scalar) const
{
    return {this->x * scalar, this->y * scalar, this->z * scalar};
}

Vector3D Vector3D::operator*(Vector3D vectorB) const
{
	return {this->x * vectorB.x, this->y * vectorB.y, this->z * vectorB.z};
}

Vector3D& Vector3D::operator*=(float scalar)
{
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;

    return *this;
}

Vector3D Vector3D::operator/(float scalar) const
{
    const float epsilon = 0.0000f;

    if (std::abs(scalar) > epsilon)
    {
        return {this->x / scalar, this->y / scalar, this->z / scalar};
    }

	throw std::runtime_error("Division by zero in Vector3D::operator/()");
}

Vector3D& Vector3D::operator/=(float scalar)
{
    const float epsilon = 0.0000f;

    if (std::abs(scalar) > epsilon)
    {
        this->x /= scalar;
        this->y /= scalar;
        this->z /= scalar;
        return *this;
    }

    throw std::runtime_error("Division by zero in Vector3D::operator/=()");
}

Vector3D Vector3D::operator-() const
{
    return {-this->x, -this->y, -this->z};
}

float Vector3D::operator[](int i) const
{
	switch(i)
	{
	case 0: return this->x;
	case 1: return this->y;
	case 2: return this->z;
	default: 
        throw std::out_of_range("Invalid index in Vector3D::operator[]");
	}
}

float& Vector3D::operator[](int i)
{
	switch(i)
	{
	case 0: return this->x;
	case 1: return this->y;
	case 2: return this->z;
	default: 
        throw std::out_of_range("Invalid index in Vector3D::operator[]");;
	}
}

void Vector3D::zero()
{
	this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
}

float Vector3D::dot(const Vector3D& vectorB) const
{
    return (this->x * vectorB.x + this->y * vectorB.y + this->z * vectorB.z);
}

Vector3D Vector3D::cross(const Vector3D& vectorB) const
{
    float newX = this->y * vectorB.z - this->z * vectorB.y;
    float newY = this->z * vectorB.x - this->x * vectorB.z;
    float newZ = this->x * vectorB.y - this->y * vectorB.x;

    return {newX, newY, newZ};
}

void Vector3D::normalize()
{
    float magnitude = this->magnitude();

    if(magnitude != 0)
    {
        this->x /= magnitude;
        this->y /= magnitude;
        this->z /= magnitude;
        return;
    }

    //std::cerr << "Vector Magnitude is 0! Operation undefined!";
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

float Vector3D::magnitude() const
{
    return std::sqrt(this->magnitudeSquared());
}

float Vector3D::magnitudeSquared() const
{
    return x * x + y * y + z * z;
}

std::ostream& utility::operator<<(std::ostream& os, const Vector3D& vector)
{
    os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
    return os;
}
