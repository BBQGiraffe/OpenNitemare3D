#ifndef _PLAYER_H
#define _PLAYER_H
#include "../../../engine/entity/Entity.h"
class Player : public Entity{
private:
	
public:
	float speed = 3;
	float rotation = 0;
	Player();
	Player(float x, float y, Camera* camera, Map map, Datreader* snd);
	void Update(float deltaTime);
	void OnCollision(Entity* sender);
	double dirX = -1.0, dirY = 0.0; //initial direction vector
	void SetRotation(float rotation);
};
#endif // !_PLAYER_H
