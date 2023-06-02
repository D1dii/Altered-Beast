#include "Enemy_Boss.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"

Enemy_Boss::Enemy_Boss(int x, int y) : Enemy(x, y) {

	// idle anim 
	idleAnim.PushBack({ 3598, 515, 126, 154 });
	currentAnim = &idleAnim;

	// Attacking anim
	attackAnim.PushBack({ 3598, 515, 126, 154 });
	attackAnim.PushBack({ 3598, 515, 126, 154 });
	attackAnim.PushBack({ 3779, 515, 126, 154 });
	attackAnim.PushBack({ 3779, 515, 126, 154 });
	attackAnim.PushBack({ 3951, 514, 126, 154 });
	attackAnim.PushBack({ 3951, 514, 126, 154 });
	attackAnim.speed = 0.5f;

	//Death animation
	deathStartAnim.PushBack({ 143, 43, 144, 180 });
	deathStartAnim.PushBack({ 455, 36, 144, 180 });
	deathStartAnim.PushBack({ 783, 36, 144, 180 });
	deathStartAnim.PushBack({ 1103, 36, 144, 180 });
	deathStartAnim.PushBack({ 1423, 43, 144, 180 });
	deathStartAnim.PushBack({ 1743, 43, 144, 180 });
	deathStartAnim.PushBack({ 2063, 36, 144, 180 });
	deathStartAnim.PushBack({ 2383, 36, 144, 180 });
	deathStartAnim.PushBack({ 2727, 43, 144, 180 });
	deathStartAnim.PushBack({ 3047, 43, 144, 180 });
	deathStartAnim.PushBack({ 3367, 43, 144, 180 });
	deathStartAnim.PushBack({ 3687, 43, 144, 180 });
	deathStartAnim.PushBack({ 4007, 43, 144, 180 });
	deathStartAnim.PushBack({ 4327, 36, 144, 180 });

	deathAnim.PushBack({ 167, 267, 144, 180 });
	deathAnim.PushBack({ 487, 260, 144, 180 });
	deathAnim.PushBack({ 807, 259, 144, 180 });
	deathAnim.PushBack({ 1127, 267, 144, 180 });
	deathAnim.PushBack({ 1447, 266, 144, 180 });
	deathAnim.PushBack({ 1767, 266, 144, 180 });
	deathAnim.PushBack({ 2087, 267, 144, 180 });
	deathAnim.PushBack({ 2407, 259, 144, 180 });
	deathAnim.PushBack({ 2727, 260, 144, 180 });
	deathAnim.PushBack({ 3047, 260, 144, 180 });
	deathAnim.PushBack({ 3367, 260, 144, 180 });
	deathAnim.PushBack({ 3687, 259, 144, 180 });
	deathAnim.PushBack({ 4007, 267, 144, 180 });
	deathAnim.PushBack({ 4327, 266, 144, 180 });
	deathAnim.PushBack({ 4655, 267, 144, 180 });

	deathFinishAnim.PushBack({ 1127, 491, 144, 180 });
	deathFinishAnim.PushBack({ 1447, 490, 144, 180 });
	deathFinishAnim.PushBack({ 2063, 484, 144, 180 });
	deathFinishAnim.PushBack({ 2375, 483, 144, 180 });
	deathFinishAnim.PushBack({ 2695, 484, 144, 180 });
	deathFinishAnim.PushBack({ 3015, 484, 144, 180 });
	deathFinishAnim.PushBack({ 3343, 491, 144, 180 });

	deathAnim.speed = 0.25f;
	deathStartAnim.speed = 0.25f;
	deathFinishAnim.speed = 0.25f;


	HitFx = App->audio->LoadFx("Assets/Fx/sonido-boss.wav");
	DeathFx = App->audio->LoadFx("Assets/Fx/sonido-muerte-boss.wav");

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
		App->audio->PlayFx(DeathFx);
		if (deathFrame <= 28) {
			currentAnim = &deathStartAnim;
			deathStartAnim.Update();
		}
		else if (deathFrame <= 328 && deathFrame > 28) {
			currentAnim = &deathAnim;
			deathAnim.Update();
		}
		else if (deathFrame <= 342 && deathFrame > 328) {
			currentAnim = &deathFinishAnim;
			deathFinishAnim.Update();
		}
		else if (deathFrame > 342) {
			SetToDelete();
			App->enemies->AddEnemy(Enemy_Type::FINAL_SCENE, 30, 40);
			
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
			position.x = position.x - 20;
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