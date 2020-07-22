#include "Entity.h"

void Entity::AddEntity(Entity* entity)
{
}

Entity::Entity()
{
	SetPosition(0, 0);
	SetRotation(0);
}

Vector2f Entity::GetPosition()
{
	return position;
}

Vector2i Entity::GetTilePosition()
{
	return Vector2i((int)position.x, (int)position.y );
}

Vector2i Entity::GetHitBox()
{
	return hitbox;
}

float Entity::GetRotation()
{
	return rotation;
}

void Entity::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}

void Entity::SetPosition(Vector2f position)
{
	SetPosition(position.x, position.y);
}

void Entity::SetRotation(float rotation)
{
	this->rotation = rotation;
}

void Entity::SetHitBox(int w, int h)
{
	hitbox = Vector2i(w, h);
}

void Entity::SetHitBox(Vector2i hitbox)
{
	this->hitbox = hitbox;
}

void Entity::Update(float deltaTime)
{
}

void Entity::OnCollision(Entity* sender)
{
}
