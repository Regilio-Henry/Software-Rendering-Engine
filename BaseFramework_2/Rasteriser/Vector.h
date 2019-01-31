#pragma once
//#include "Rasteriser.h"

class Vector
{
public:
	Vector();
	Vector(float x, float y, float z);
	Vector(const Vector& other);

	// Accessors
	float GetX() const;
	void SetX(const float x);
	float GetY() const;
	void SetY(const float y);
	float GetZ() const;
	void SetZ(const float z);
	float Magnitude(Vector vec);
	float DotProduct(Vector opperand);
	Vector CrossProduct(Vector opperand);
	void Normalise();
	// Assignment operator
	Vector& operator= (const Vector& rhs);
	bool operator== (const Vector& rhs) const;
	const Vector operator+ (const Vector& rhs) const;
	const Vector operator- (const Vector& rhs) const;

private:
	float _x;
	float _y;
	float _z;
};
