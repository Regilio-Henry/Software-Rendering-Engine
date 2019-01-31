#include <algorithm> 
#include "Vector.h"
#include <vector>

class DirectionaLighting
{
public:
	DirectionaLighting();
	DirectionaLighting(Vector _lightDirection, float r, float g, float b);
	~DirectionaLighting();
	void setRed(float redIntensity);
	float getRed() const;
	void setBlue(float blueIntensity);
	float getBlue() const;
	void setGreen(float greenIntensity);
	float getGreen() const;
	Vector getLightDirection() const;
	void setLightDirection(Vector lightDirection) ;
private:
	float _redIntensity;
	float _greenIntensity;
	float _blueIntensity;
	Vector lightDirection;
};