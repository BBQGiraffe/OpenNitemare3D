#ifndef _ENTITY_H
#define _ENTITY_H
#include "../camera/Camera.h"
#include "../map/Map.h"
#include "../sounds/Sounds.h"
#include "../../engine/sound/Sound.h"
#include "../dat/Datreader.h"
#include <vector>
class Entity {

protected:
	Vector2f position;
	Vector2i tilePosition;
	Vector2i hitbox;
	Datreader* snd;
	
	float rotation;
	std::vector<Entity*>* entities;

	void AddEntity(Entity* entity);
	Camera* camera;
	Map* map;

public:
	enum Direction {
		NORTH,
		EAST,
		SOUT,
		WEST
	};
	enum Type {
		STATIC,
		NPC,
		PLAYER,
		PICKUP,
		PUSHABLE
	};
	Direction direction;
	Type type;
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