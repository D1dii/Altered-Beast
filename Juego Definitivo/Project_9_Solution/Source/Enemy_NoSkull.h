#ifndef __ENEMY_NOSKULL_H__
#define __ENEMY_NOSKULL_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_NoSkull : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_NoSkull(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void OnCollision(Collider* collider) override;

	void SetToDelete() override;

private:

	Path path;

	bool touch = true;

	Collider* attack = nullptr;

	// Zombie animations
	Animation walking;
	Animation punchZombie;
	Animation firstHit;

	enum class state
	{
		WALK,
		WALK_2,
		PUNCH_ZOMBIE,
		
	};

	state zombieState = state::WALK;

	int life = 2;

	int frame = 0;
	int punchFrame = 0;
};


#endif // __ENEMY_NOSKULL_H__
