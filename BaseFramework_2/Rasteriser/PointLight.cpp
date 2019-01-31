#include "PointLight.h"

PointLight::PointLight()
{
	_redIntensity = 1;
	_blueIntensity = 1;
	_greenIntensity = 1;
	_position = Vertex(0,0,0);
	r_a = 0.5;
	r_b = 0.5;
	r_c = 0.5;
}

PointLight::PointLight(Vertex position, float r, float g, float b, float _a, float _b, float _c)
{
	_redIntensity = r;
	_blueIntensity = b;
	_greenIntensity = g;
	_position = position;
	r_a = _a;
	r_b = _b;
	r_c = _c;
}

PointLight::~PointLight()
{
}

void PointLight::setRed(float redIntensity)
{
	_redIntensity = redIntensity;
}

float PointLight::getRed() const
{
	return _redIntensity;
}

void PointLight::setBlue(float blueIntensity)
{
	_blueIntensity = blueIntensity;
}

float PointLight::getBlue() const
{
	return _blueIntensity;
}

void PointLight::setGreen(float greenIntensity)
{
	_greenIntensity = greenIntensity;
}

float PointLight::getGreen() const
{
	return _greenIntensity;
}

Vertex PointLight::getPosition() const
{
	return _position;
}

void PointLight::setPosition(Vertex position)
{
	_position = position;
}

void PointLight::setA(float _a)
{
	r_a = _a;
}

float PointLight::getA() const
{
	return r_a;
}

void PointLight::setB(float _b)
{
	r_b = _b;
}

float PointLight::getB() const
{
	return r_b;
}

void PointLight::setC(float _c)
{
	r_c = _c;
}

float PointLight::getC() const
{
	return r_c;
}
