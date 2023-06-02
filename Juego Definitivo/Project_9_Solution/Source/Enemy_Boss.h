#ifndef __ENEMY_BOSS_H__
#define __ENEMY_BOSS_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Boss : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Boss(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void OnCollision(Collider* collider) override;

	void SetToDelete() override;

private:

	Path path;

	bool touch = true;

	// Zombie animations
	Animation idleAnim;
	Animation attackAnim;
	Animation hitAnim;
	Animation deathStartAnim;
	Animation deathAnim;
	Animation deathFinishAnim;
	

	enum class state
	{
		IDLE,
		ATTACK,
		GET_HIT,
		DEATH,

	};

	state bossState = state::IDLE;

	uint HitFx = 0;
	uint DeathFx = 0;

	int life = 1;

	int frame = 0;
	int attackFrame = 0;
	int deathFrame = 0;
	int touchFrame = 0;
	
};


#endif // __ENEMY_BOSS_H__