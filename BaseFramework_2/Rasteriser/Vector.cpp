#include "Vector.h"
#include <math.h>

Vector::Vector()
{
	_x = 0.0f;
	_y = 0.0f;
	_z = 0.0f;
}

Vector::Vector(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}

Vector::Vector(const Vector& other)
{
	_x = other.GetX();
	_y = other.GetY();
	_z = other.GetZ();
}

float Vector::GetX() const
{
	return _x;
}

void Vector::SetX(const float x)
{
	_x = x;
}

float Vector::GetY() const
{
	return _y;
}

void Vector::SetY(const float y)
{
	_y = y;
}

float Vector::GetZ() const
{
	return _z;
}

void Vector::SetZ(const float z)
{
	_z = z;
}

float Vector::DotProduct(Vector opperand)
{
	
	return ((_x * opperand.GetX()) + (_y * opperand.GetY()) + (_z * opperand.GetZ()));
}

float Vector::Magnitude(Vector vec)
{
	return (float)sqrt((pow(vec.GetX(), 2)) + (pow(vec.GetY(), 2)) + (pow(vec.GetZ(), 2)));
}

Vector Vector::CrossProduct(Vector opperand)
{
	float a = ((_y * opperand.GetZ() ) - (_z * opperand.GetY()));
	float b = (_z * (opperand.GetX()) - (_x * opperand.GetZ()));
	float c = ((_x * opperand.GetY()) - (_y * opperand.GetX()));
	return Vector(a, b, c);
}

void Vector::Normalise()
{
	float lenght = Magnitude(Vector(_x,_y, _z));
	_x = _x / lenght;
	_y = _y / lenght;
	_z = _z / lenght;
}

Vector& Vector::operator=(const Vector& rhs)
{
	// Only do the assignment if we are not assigning
	// to ourselves
	if (this != &rhs)
	{
		_x = rhs.GetX();
		_y = rhs.GetY();
		_z = rhs.GetZ();
	}
	return *this;
}

// The const at the end of the declaraion for '==" indicates that this operation does not change
// any of the member variables in this class.

bool Vector::operator==(const Vector& rhs) const
{
	return (_x == rhs.GetX() && _y == rhs.GetY() && rhs.GetZ());
}

const Vector Vector::operator+(const Vector& rhs) const
{
	
	return Vector(_x + rhs.GetX(), _y + rhs.GetY(), _z + rhs.GetZ());
}

const Vector Vector::operator-(const Vector& rhs) const
{

	return Vector(_x - rhs.GetX(), _y - rhs.GetY(), _z - rhs.GetZ());
}
