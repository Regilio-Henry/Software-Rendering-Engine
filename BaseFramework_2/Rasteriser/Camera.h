#pragma once
#include "Matrix.h"

class Camera
{
public:
	Camera(float xRotation, float yRotation, float zRotation, const Vertex& position);
	Camera();


	// Accessors
	float GetXRotation() const;
	void SetXRotation(const float xRotation);
	float GetYRotation() const;
	void SetYRotation(const float yRotation);
	float GetZRotation() const;
	void SetZRotation(const float zRotation);
	Vertex GetPosition() const;
	void SetPosition(const Vertex position);
	void CameraTransform();
	Matrix GetCameraMatrix();

private:
	float _xRotation;
	float _yRotation;
	float _zRotation;
	Vertex _position;
	Matrix _cameraMatrix;
};