#include "Enemy_Boss.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"

Enemy_Boss::Enemy_Boss(int x, int y) : Enemy(x, y) {

	// idle anim 
	idleAnim.PushBack({ 15, 14, 126, 154 });
	currentAnim = &idleAnim;

	// Attacking anim
	attackAnim.PushBack({ 15, 14, 126, 154 });
	attackAnim.PushBack({ 15, 14, 126, 154 });
	attackAnim.PushBack({ 12, 192, 126, 154 });
	attackAnim.PushBack({ 12, 192, 126, 154 });
	attackAnim.PushBack({ 146, 191, 126, 154 });
	attackAnim.PushBack({ 146, 191, 126, 154 });
	attackAnim.speed = 0.5f;

}

void Enemy_Boss::Update() {



	switch (bossState)
	{
	case Enemy_Boss::state::IDLE:
		currentAnim = &idleAnim;
		idleAnim.Update();
		frame++;
		if (frame >= 50) {
			bossState = state::ATTACK;
			frame = 0;
		}
		break;
	case Enemy_Boss::state::ATTACK:
		currentAnim = &attackAnim;
		attackAnim.Update();
		frame++;
		attackFrame++;
		if (attackFrame >= 12) {
			App->enemies->AddEnemy(Enemy_Type::BOSS_HEAD, position.x + 50, position.y + 5);
			attackFrame = 0;
		}

		if (frame >= 48) {
			bossState = state::IDLE;
			frame = 0;
		}
		break;
	case Enemy_Boss::state::GET_HIT:

		break;
	case Enemy_Boss::state::DEATH:

		break;
	}

}

void Enemy_Boss::OnCollision(Collider* col) {

}

void Enemy_Boss::SetToDelete() {

}