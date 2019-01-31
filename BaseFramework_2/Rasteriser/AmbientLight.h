#pragma once
#include <algorithm> 
#include "Vector.h"
#include <vector>

class AmbientLight
{
public:
	AmbientLight();
	AmbientLight(float r, float g, float b);
	~AmbientLight();
	void setRed(float redIntensity);
	float getRed() const;
	void setBlue(float blueIntensity);
	float getBlue() const;
	void setGreen(float greenIntensity);
	float getGreen() const;
private:
	float _redIntensity;
	float _greenIntensity;
	float _blueIntensity;
};