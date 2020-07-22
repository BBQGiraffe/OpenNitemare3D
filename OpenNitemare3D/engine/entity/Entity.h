#ifndef _ENTITY_H
#define _ENTITY_H
#include "../camera/Camera.h"
#include "../map/Map.h"
#include <vector>
class Entity {

protected:
	Vector2f position;
	Vector2i tilePosition;
	Vector2i hitbox;
	int sprite;
	float rotation;
	std::vector<Entity*>* entities;

	void AddEntity(Entity* entity);
	Camera* camera;
	Map map;

public:
	Entity();
	
	//getters
	Vector2f GetPosition();
	Vector2i GetTilePosition();
	Vector2i GetHitBox();
	float GetRotation();

	//setters
	void SetPosition(float x, float y);
	void SetPosition(Vector2f position);
	void SetRotation(float rotation);
	void SetHitBox(int w, int h);
	void SetHitBox(Vector2i hitbox);

	

	//functions
	void Update(float deltaTime);
	void OnCollision(Entity* sender);


};

#endif