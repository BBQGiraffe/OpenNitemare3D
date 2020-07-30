#include "Player.h"
#include <SDL.h>
#include <iostream>
Player::Player()
{
	
}

Player::Player(float x, float y, Camera* camera, Map map, Datreader* snd)
{
	SetPosition(x, y);
	this->camera = camera;
	this->map = &map;
	this->snd = snd;
	Sound::PlaySound(PLAYER_PLASMA_PISTOL_FIRE, *this->snd);
	SetRotation(-1.57f);
}

void Player::Update(float deltaTime)
{
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
	if (state[SDL_SCANCODE_SPACE]) {
		Sound::PlaySound(PLAYER_PLASMA_PISTOL_FIRE, *this->snd);
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



void Player::SetRotation(float rotation)
{
	float oldRot = this->rotation;
	dirX = cos(rotation);
	dirY = sin(rotation);
	float oldPlaneX = camera->planeX;
	camera->planeX = camera->planeX * cos(rotation - oldRot) - camera->planeY * sin(rotation - oldRot);
	camera->planeY = oldPlaneX * sin(rotation - oldRot) + camera->planeY * cos(rotation - oldRot);

	this->rotation = rotation;
}
