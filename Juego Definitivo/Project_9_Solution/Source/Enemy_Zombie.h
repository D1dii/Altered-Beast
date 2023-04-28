#ifndef __ENEMY_ZOMBIE_H__
#define __ENEMY_ZOMBIE_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Zombie : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Zombie(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void OnCollision(Collider* collider);

private:

	Path path;

	// Zombie animations
	Animation walking;
	Animation exploding;
};


#endif // __ENEMY_ZOMBIE_H__
