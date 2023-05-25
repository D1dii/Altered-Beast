#ifndef __ENEMY_ORCO_H__
#define __ENEMY_ORCO_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Orco : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Orco(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void OnCollision(Collider* collider) override;

	void SetToDelete() override;

private:

	Path path;

	bool touch = true;

	Collider* punchAttack = nullptr;

	// Zombie animations
	Animation walking;
	Animation punchOrco;
	Animation Hit;
	Animation death;
	Animation idle;

	enum class state
	{
		WALK,
		HIT,
		PUNCH_ORCO,
		DEATH,

	};

	state orcoState = state::WALK;

	int life = 2;

	int frame = 0;
	int punchFrame = 0;
};


#endif // __ENEMY_ORCO_H__

