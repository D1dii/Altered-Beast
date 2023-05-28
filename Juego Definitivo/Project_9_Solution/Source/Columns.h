#ifndef __Columns_H__
#define __Columns_H__

#include "Enemy.h"
#include "Path.h"

class Columns : public Enemy
{

public:
	Columns(int x, int y);

	void Update() override;

	void OnCollision(Collider* col) override;

	void SetToDelete() override;

private:
	Path path;

	Animation noAnim;
	Animation idle;
	Animation shaking;
	Animation spawnAnim;

	int frame = 0;

};

#endif


