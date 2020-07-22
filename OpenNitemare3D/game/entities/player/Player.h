#ifndef _PLAYER_H
#define _PLAYER_H
#include "../../../engine/entity/Entity.h"
class Player : public Entity{
private:
	
public:
	float speed = 3;
	float rotation = 0;
	Player();
	Player(float x, float y, Camera* camera, Map map);
	void Update(float deltaTime);
	void OnCollision(Entity* sender);
	void SetRotation_(float rot);
	double dirX = -1.0, dirY = 0.0; //initial direction vector

};
#endif // !_PLAYER_H
