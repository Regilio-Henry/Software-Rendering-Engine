#include "Camera.h"

Camera::Camera(float xRotation, float yRotation, float zRotation, const Vertex & position)
{
	_xRotation = xRotation;
	_yRotation = yRotation;
	_zRotation = zRotation;
	_position = position;
	CameraTransform();
}

Camera::Camera()
{
	_xRotation = 0;
	_yRotation = 0;
	_zRotation = 0;
	_position = Vertex(0,0, -50);
	CameraTransform();
}

float Camera::GetXRotation() const
{
	return _xRotation;
}

void Camera::SetXRotation(const float xRotation)
{
	_xRotation = xRotation;
	CameraTransform();
}

float Camera::GetYRotation() const
{
	return _yRotation;
}

void Camera::SetYRotation(const float yRotation)
{
	_yRotation = yRotation;
	CameraTransform();
}

float Camera::GetZRotation() const
{
	return _zRotation;
}

void Camera::SetZRotation(const float zRotation)
{
	_zRotation = zRotation;
	CameraTransform();
}

Vertex Camera::GetPosition() const
{
	return _position;
}

void Camera::SetPosition(const Vertex position)
{
	_position = position;
	CameraTransform();
}

Matrix Camera::GetCameraMatrix()
{
	return _cameraMatrix;
}

//Generates Matrix for the camera transform
void Camera::CameraTransform()
{
	_cameraMatrix = (Matrix().XYZRotationMatrix(_xRotation, _yRotation, _zRotation) * Matrix().TranslationMatrix(_position.GetX() *-1, _position.GetY()*-1, _position.GetZ()*-1));

}

