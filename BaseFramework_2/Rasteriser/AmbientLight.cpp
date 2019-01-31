#include "AmbientLight.h"

AmbientLight::AmbientLight()
{
	_redIntensity = 1;
	_blueIntensity = 1;
	_greenIntensity = 1;

}

AmbientLight::AmbientLight(float r, float g, float b)
{
	_redIntensity = r;
	_blueIntensity = b;
	_greenIntensity = g;
}

AmbientLight::~AmbientLight()
{
}

void AmbientLight::setRed(float redIntensity)
{
	_redIntensity = redIntensity;
}

float AmbientLight::getRed() const
{
	return _redIntensity;
}

void AmbientLight::setBlue(float blueIntensity)
{
	_blueIntensity = blueIntensity;
}

float AmbientLight::getBlue() const
{
	return _blueIntensity;
}

void AmbientLight::setGreen(float greenIntensity)
{
	_greenIntensity = greenIntensity;
}

float AmbientLight::getGreen() const
{
	return _greenIntensity;
}