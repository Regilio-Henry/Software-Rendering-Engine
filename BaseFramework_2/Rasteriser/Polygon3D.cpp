#include "Polygon3D.h"

Polygon3D::Polygon3D()
{
	_indices[0] = 0;
	_indices[1] = 0;
	_indices[2] = 0;
	_isCulled = false;
	_color = RGB(0, 0, 0);
}

Polygon3D::Polygon3D(int index0, int index1, int index2)
{
	_indices[0] = index0;
	_indices[1] = index1;
	_indices[2] = index2;
	_isCulled = false;
	_color = RGB(0, 0, 0);
}

Polygon3D::~Polygon3D()
{
}



Polygon3D::Polygon3D(const Polygon3D & p)
{
	for (int i = 0; i < 3; i++)
	{
		_indices[i] = p.GetIndex(i);
	}
	_isCulled = p.GetIsCulled();
	_zDepth = p.GetZDepth();
	_color = p.GetColor();
}

int Polygon3D::GetIndex(int index) const
{
	return _indices[index];
}

Polygon3D & Polygon3D::operator=(const Polygon3D & rhs)
{
	if (this != &rhs)
	{
		for (int i = 0; i < 3; i++)
		{
			_indices[i] = rhs.GetIndex(i);
		}
		_isCulled = rhs.GetIsCulled();
		_zDepth = rhs.GetZDepth();
		_color = rhs.GetColor();
	}
	return *this;
}

bool Polygon3D::GetIsCulled() const
{
	return _isCulled;
}

void Polygon3D::SetIsCulled(bool cull)
{
	_isCulled = cull;
}

void Polygon3D::SetNormal(Vector normal)
{
	_normal = normal;
}

Vector Polygon3D::GetNormal()
{
	return _normal;
}

void Polygon3D::SetZDepth(float zDepth)
{
	_zDepth = zDepth;
}

float Polygon3D::GetZDepth() const
{
	return _zDepth;
}

COLORREF Polygon3D::GetColor() const
{
	return _color;
}

void Polygon3D::SetColor(COLORREF color)
{
	_color = color;
}
