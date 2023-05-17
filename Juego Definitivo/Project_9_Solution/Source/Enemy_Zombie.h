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

	void OnCollision(Collider* collider) override;

	void SetToDelete() override;

private:

	Path path;

	bool touch = true;

	Collider* explosion = nullptr;
	Collider* collision = nullptr;

	// Zombie animations
	Animation walking;
	Animation noHead;
	Animation headExplosion;
	Animation noHeadExplosion;
	Animation firstHit;

	enum class state
	{
		WALK,
		NO_HEAD,
		EXPLOSIONHEAD,
		EXPLOSION_NO_HEAD
	};

	state zombieState = state::WALK;

	int life = 2;

	int frame = 0;
};


#endif // __ENEMY_ZOMBIE_H__
