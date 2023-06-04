#ifndef __INVOCADOR_BOSS_H__
#define __INVOCADOR_BOSS_H__

#include "Enemy.h"
#include "Path.h"

class Invocador_Boss : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Invocador_Boss(int x, int y);

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
	Animation invocarBoss;


	enum class state
	{
		IDLE,
		INVOCAR,

	};

	state invocadorState = state::IDLE;

	uint welcomeFx = 0;
	

	int life = 60;

	int frame = 0;
	int waitFrame = 0;
	

	bool defeated = false;

};


#endif // __INVOCADOR_BOSS_H__
