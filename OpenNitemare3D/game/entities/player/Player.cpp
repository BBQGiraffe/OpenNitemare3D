#include "Player.h"
#include <SDL.h>
#include <iostream>
Player::Player()
{
	
}

Player::Player(float x, float y, Camera* camera, Map map)
{
	SetPosition(x + 20, y);
	SetRotation(0);
	this->camera = camera;
	this->map = map;

}

void Player::Update(float deltaTime)
{
	//SetRotation_(90);
	float rotSpeed = deltaTime * 3; //the constant value is in radians/second
	float oldRot = rotation;
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_UP]) {
		
		//if (worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
		//if (worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
		
		position.x += dirX * speed * deltaTime;
		position.y += dirY * speed * deltaTime;

	}
	if (state[SDL_SCANCODE_LEFT]) {
		rotation -= rotSpeed;
	}

	if (state[SDL_SCANCODE_RIGHT]) {
		rotation += rotSpeed;
	}

	dirX = cos(rotation);
	dirY = sin(rotation);
	float oldPlaneX = camera->planeX;
	camera->planeX = camera->planeX * cos(rotation - oldRot) - camera->planeY * sin(rotation - oldRot);
	camera->planeY = oldPlaneX * sin(rotation-oldRot) + camera->planeY*cos(rotation - oldRot);
}

void Player::OnCollision(Entity* sender)
{
}

void Player::SetRotation_(float rot)
{
	camera->planeX = camera->planeX * cos(rot) - camera->planeY * sin(rot);
	camera->planeY = camera->planeX * sin(rot) + camera->planeY * cos(rot);
}
