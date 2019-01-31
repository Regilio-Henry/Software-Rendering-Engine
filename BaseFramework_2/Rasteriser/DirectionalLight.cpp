#include "DirectionalLight.h"

DirectionaLighting::DirectionaLighting()
{
	lightDirection = Vector(1,1,1);
	_redIntensity = 1;
	_blueIntensity = 1;
	_greenIntensity = 1;
	
}

DirectionaLighting::DirectionaLighting(Vector _lightDirection, float r, float g, float b)
{
	lightDirection = _lightDirection;
	_redIntensity = r;
	_blueIntensity = b;
	_greenIntensity = g;
}

DirectionaLighting::~DirectionaLighting()
{
}

void DirectionaLighting::setRed(float redIntensity)
{
	_redIntensity = redIntensity;
}

float DirectionaLighting::getRed() const
{
	return _redIntensity;
}

void DirectionaLighting::setBlue(float blueIntensity)
{
	_blueIntensity = blueIntensity;
}

float DirectionaLighting::getBlue() const
{
	return _blueIntensity;
}

void DirectionaLighting::setGreen(float greenIntensity)
{
	_greenIntensity = greenIntensity;
}

float DirectionaLighting::getGreen() const
{
	return _greenIntensity;
}

Vector DirectionaLighting::getLightDirection() const
{
	return lightDirection;
}

void DirectionaLighting::setLightDirection(Vector _lightDirection)
{
	lightDirection = _lightDirection;
}
