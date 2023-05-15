#include "Enemy_Wolf_Blue.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"

Enemy_Wolf_Blue::Enemy_Wolf_Blue(int x, int y) : Enemy(x, y) {

	// idle animation
	idle.PushBack({ 172, 14, 66, 47 });
	currentAnim = &idle;

	// Moving animation
	jumpUp.PushBack({ 5, 14, 66, 47 });
	jumpUp.speed = 0.1f;

	jumpDown.PushBack({ 95, 14, 66, 47 });
	jumpDown.speed = 0.1f;

	// Dead animation
	dead.PushBack({ 256, 21, 31, 31 });
	dead.PushBack({ 304, 30, 15, 15 });
	dead.speed = 0.1f;


	path.PushBack({ -1.5f, -1.5f }, 20, &jumpUp);
	path.PushBack({ -1.5f, 1.5f }, 20, &jumpDown);
	path.PushBack({ 0.0f, 0.0f }, 40, &idle);

	collider = App->collisions->AddCollider({ 0, 0, 55, 20 }, Collider::Type::ENEMY, (Module*)App->enemies);

}

void Enemy_Wolf_Blue::Update() {


	switch (WolfState) {
	case state::IDLE:
		currentAnim = &idle;
		idle.Update();
		frame++;
		if (frame > 100) {
			WolfState = state::WALK;
			frame = 0;
		}
		break;
	case state::WALK:
		path.Update();
		currentAnim = path.GetCurrentAnimation();
		position = spawnPos + path.GetRelativePosition();
		break;
	case state::DEAD:
		currentAnim = &dead;
		dead.Update();
		frame++;
		if (frame >= 20) {
			SetToDelete();
			App->enemies->AddEnemy(Enemy_Type::POWER_UP, position.x + 50, position.y - 10);
		}
	}

	Enemy::Update();
	collider->SetPos(position.x + 10, position.y + 15);
}

void Enemy_Wolf_Blue::OnCollision(Collider* col) {
	if (col->type == col->PLAYER_ATTACK && touch == true) {
		App->player->score += 100;
		WolfState = state::DEAD;
		touch = false;
	}
}

void Enemy_Wolf_Blue::SetToDelete() {
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}