#ifndef __BOSS_HEAD_H__
#define __BOSS_HEAD_H__

#include "Enemy.h"
#include "Path.h"

class Boss_Head : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Boss_Head(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void OnCollision(Collider* collider) override;

	void SetToDelete() override;

private:

	Path LaunchPath;
	Path attackPath;

	int randomPos;

	int limitFrames;

	bool touch = true;

	// Zombie animations
	Animation launchAnim;
	Animation attackAnim;
	Animation deathAnim;


	enum class state
	{
		LAUNCH,
		ATTACK,
		DEATH,

	};

	state headState = state::LAUNCH;

	int life = 1;

	int frame = 0;
	int punchFrame = 0;
};


#endif // __BOSS_HEAD_H__
