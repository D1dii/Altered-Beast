#ifndef __SPIRIT_BALL_H__
#define __SPIRIT_BALL_H__

#include "Enemy.h"
#include "Path.h"

class Spirit_Ball : public Enemy 
{

public:
	Spirit_Ball(int x, int y);

	void Update() override;

	void OnCollision(Collider* col) override;

	void SetToDelete() override;

private:
	Path path;

	Animation idle;

	int frame = 0;

};

#endif
