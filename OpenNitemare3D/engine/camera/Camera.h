#ifndef _CAMERA_H
#define _CAMERA_H
#include "../math/Vector2f.h"
#include <iostream>
#include "../math/Vector2i.h"
class Camera {
private:
	Vector2f plane;
	Vector2f position;
	Vector2i gridPosition;
	float rotation;
public:
	Camera();
	
	//setters
	void SetPosition(Vector2f position);
	void SetPosition(float x, float y);
	void SetRotation(float rotation);
	double planeX = -0, planeY = 0.66; //the 2d raycaster version of camera plane


	//getters
	Vector2f GetPosition();
	Vector2i GetGridPosition();
	float GetRotation();
};


#endif