#include "Enemy_Dragon.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"

Enemy_Dragon::Enemy_Dragon(int x, int y) : Enemy(x, y) {

	// Flying Anim
	flying.PushBack({ 2, 15, 56, 69 });
	flying.PushBack({ 71, 19, 44, 69 });
	flying.PushBack({ 134, 15, 44, 69 });
	flying.speed = 0.15f;
	currentAnim = &flying;

	path.PushBack({ -0.35f, 0.75f }, 30, &flying);
	path.PushBack({ -0.35f, -0.75f }, 30, &flying);

	attackPath.PushBack({ 1.0f, 0.9f }, 30, &flying);

}

void Enemy_Dragon::Update() {
	
	if (attacking) {
		position = spawnPos + attackPath.GetRelativePosition();
	}
	else {
		position = spawnPos + path.GetRelativePosition();
	}

	switch (dragonState)
	{
	case Enemy_Dragon::state::FLY:
		currentAnim = path.GetCurrentAnimation();
		path.Update();
		if (position.x <= App->render->camera.x + 20) {
			dragonState = state::ATTACK;
			attacking = true;
		}
		break;
	case Enemy_Dragon::state::ATTACK:
		currentAnim = attackPath.GetCurrentAnimation();
		UpdatePath();
		attackPath.Update();
		break;
	case Enemy_Dragon::state::DEAD:

		break;
	}

	Enemy::Update();

}

void Enemy_Dragon::UpdatePath() {
	if (position.x > App->player->position.x) {
		attackPath.relativePosition.x -= 2;
	}
	else if (position.x < App->player->position.x) {
		attackPath.relativePosition.x += 1;
	}
}

void Enemy_Dragon::OnCollision(Collider* col) {

}

void Enemy_Dragon::SetToDelete() {

}