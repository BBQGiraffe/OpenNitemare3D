#include "Camera.h"

Camera::Camera()
{
	//planeX = -0.65;
	//planeY = 0.01;
}

void Camera::SetPosition(Vector2f position)
{
	SetPosition(position.x, position.y);
}

void Camera::SetPosition(float x, float y)
{
	position = Vector2f(x, y);
	
}

void Camera::SetRotation(float rotation)
{
	this->rotation = rotation;
}

Vector2f Camera::GetPosition()
{
	return position;
}

Vector2i Camera::GetGridPosition()
{
	return Vector2i(position.x / 64, position.y / 64);
}

float Camera::GetRotation()
{
	return rotation;
}
