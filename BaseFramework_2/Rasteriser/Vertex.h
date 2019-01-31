#pragma once
#include "Vector.h"
#include <windows.h>

class Vertex
{
public:
	Vertex();
	Vertex(float x, float y, float z);
	Vertex(const Vertex& other);

	// Accessors
	float GetX() const;
	void SetX(const float x);
	float GetY() const;
	void SetY(const float y);
	float GetW() const;
	void SetW(const float w);
	float GetZ() const;
	void SetZ(const float z);
	void DehomogenizeVertex();
	void SetNormal(Vector normal);
	Vector GetNormal() const;
	COLORREF GetColor()const;
	void SetColor(COLORREF color);
	float GetContribution()const;
	void SetContribution(float contribution);

	// Assignment operator
	Vertex& operator= (const Vertex& rhs);

	bool operator== (const Vertex& rhs) const;

	const Vertex operator+ (const Vertex& rhs) const;
	const Vector operator- (const Vertex& rhs) const;

private:
	float _x;
	float _y;
	float _z;
	float _w;
	Vector _normal;
	COLORREF _color;
	float _contribution;
};

