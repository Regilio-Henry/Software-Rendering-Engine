#pragma once
#include <algorithm> 
#include "Vertex.h"
#include <vector>

class PointLight
{
public:
	PointLight();
	PointLight(Vertex position, float r, float g, float b, float _a, float _b, float _c);
	~PointLight();
	void setRed(float redIntensity);
	float getRed() const;
	void setBlue(float blueIntensity);
	float getBlue() const;
	void setGreen(float greenIntensity);
	float getGreen() const;
	Vertex getPosition() const;
	void setPosition(Vertex position);
	void setA(float _a);
	float getA() const;
	void setB(float _b);
	float getB() const;
	void setC(float _c);
	float getC() const;
private:
	float _redIntensity;
	float _greenIntensity;
	float _blueIntensity;
	Vertex _position;
	float r_a; 
	float r_b; 
	float r_c;
};