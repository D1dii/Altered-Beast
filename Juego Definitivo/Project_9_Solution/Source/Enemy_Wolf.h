#ifndef __ENEMY_WOLF_H__
#define __ENEMY_WOLF_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Wolf : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Wolf(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void OnCollision(Collider* collider) override;

	void SetToDelete() override;

private:

	Path path;

	bool touch = true;

	Collider* explosion = nullptr;

	// Zombie animations
	Animation jumpUp;
	Animation jumpDown;
	Animation idle;
	Animation dead;
	

	enum class state
	{
		WALK,
		IDLE,
		DEAD,

	};

	state WolfState = state::WALK;

	int life = 2;

	int frame = 0;
};


#endif // __ENEMY_WOLF_H__
