#ifndef __ENEMY_DRAGON_H__
#define __ENEMY_DRAGON_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Dragon : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Dragon(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void UpdatePath();

	void OnCollision(Collider* collider) override;

	void SetToDelete() override;

private:

	Path path;
	Path attackPath;

	bool attacking = false;

	bool touch = true;

	Collider* explosion = nullptr;

	// Zombie animations
	Animation flying;
	Animation dead;

	enum class state
	{
		FLY,
		ATTACK,
		DEAD
	};

	state dragonState = state::FLY;

	int life = 2;

	int frame = 0;
};


#endif // __ENEMY_ZOMBIE_H__
