#ifndef __FINAL_CUTSCENE_H__
#define __FINAL_CUTSCENE_H__

#include "Enemy.h"
#include "Path.h"

class Final_Cutscene : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Final_Cutscene(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void OnCollision(Collider* collider) override;

	void SetToDelete() override;


private:

	Path path;

	bool touch = true;

	// Zombie animations
	Animation sceneAnim;

	int frame = 0;

	uint LaughFx = 0;

};


#endif // __FINAL_CUTSCENE_H__
