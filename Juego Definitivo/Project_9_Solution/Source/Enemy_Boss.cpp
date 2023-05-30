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

	HitFx = App->audio->LoadFx("Assets/Fx/sonido-boss.wav");

	receiveDmg = App->collisions->AddCollider({ position.x + 10, position.y - 10, 130, 165 }, Collider::Type::ENEMY, (Module*)App->enemies);
	afflictDmg = App->collisions->AddCollider({ position.x + 25, position.y + 30, 90, 125 }, Collider::Type::ENEMY_SHOT, (Module*)App->enemies);

}

void Enemy_Boss::Update() {



	switch (bossState)
	{
	case Enemy_Boss::state::IDLE:
		currentAnim = &idleAnim;
		idleAnim.Update();
		frame++;
		touchFrame++;
		if (touch == false && touchFrame >= 30) {
			touch = true;
			touchFrame = 0;
		}
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
		touchFrame++;
		if (attackFrame >= 12) {
			App->enemies->AddEnemy(Enemy_Type::BOSS_HEAD, position.x + 50, position.y + 5);
			attackFrame = 0;
		}
		if (touch == false && touchFrame >= 30) {
			touch = true;
			touchFrame = 0;
		}
		if (frame >= 48) {
			bossState = state::IDLE;
			frame = 0;
		}
		break;
	case Enemy_Boss::state::GET_HIT:

		break;
	case Enemy_Boss::state::DEATH:
		deathFrame++;
		if (deathFrame >= 20) {
			SetToDelete();
		}
		break;
	}

}

void Enemy_Boss::OnCollision(Collider* col) {
	if (col->type == col->PLAYER_ATTACK && touch == true) {
		life--;
		App->audio->PlayFx(HitFx);
		touch = false;
		if (life == 0) {
			App->player->score += 1000000;
			bossState = state::DEATH;
			App->collisions->RemoveCollider(afflictDmg);
		}
	}
}

void Enemy_Boss::SetToDelete() {
	pendingToDelete = true;
	if (receiveDmg != nullptr)
		receiveDmg->pendingToDelete = true;
	if (afflictDmg != nullptr)
		afflictDmg->pendingToDelete = true;
}