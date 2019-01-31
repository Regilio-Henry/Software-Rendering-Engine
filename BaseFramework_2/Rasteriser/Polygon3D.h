#pragma once
#include "Vector.h"
#include "Rasteriser.h"

class Polygon3D
{
public:
	Polygon3D();
	Polygon3D(int index0, int index1, int index2);
	~Polygon3D();
	Polygon3D(const Polygon3D& p);
	// Accessor to return index of specified vertex
	int GetIndex(int index) const;
	Polygon3D& operator= (const Polygon3D &rhs);
	bool GetIsCulled() const;
	void SetIsCulled(bool cull);
	void SetNormal(Vector normal);
	Vector GetNormal();
	void SetZDepth(float zDepth);
	float GetZDepth() const;
	COLORREF GetColor()const;
	void SetColor(COLORREF color);

private:
	COLORREF _color;
	int _indices[3];
	bool _isCulled;
	Vector _normal;
	float  _zDepth;
};