#include "Enemy_Dragon.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"

Enemy_Dragon::Enemy_Dragon(int x, int y) : Enemy(x, y) {

	// Flying Anim
	flying.PushBack({ 2, 15, 56, 69 });
	flying.PushBack({ 71, 19, 44, 69 });
	flying.PushBack({ 134, 15, 44, 69 });
	flying.speed = 0.15f;
	currentAnim = &flying;

	dead.PushBack({ 56, 102, 39, 47 });
	dead.PushBack({ 126, 123, 56, 17 });
	dead.PushBack({ 206, 117, 43, 39 });
	dead.speed = 0.15f;

	path.PushBack({ -0.35f, 0.75f }, 30, &flying);
	path.PushBack({ -0.35f, -0.75f }, 30, &flying);

	path2.PushBack({ -0.35f, 0.75f }, 30, &flying);
	path2.PushBack({ -0.35f, -0.75f }, 30, &flying);

	attackPath.PushBack({ 1.0f, 0.9f }, 30, &flying);

	deathPath.PushBack({ -1.5f, -1.0f }, 30, &dead);

	repositionPath.PushBack({ 1.0f, -0.5f }, 30, &flying);

	receiveDmg = App->collisions->AddCollider({ position.x - 10, position.y - 10, 45, 70 }, Collider::Type::ENEMY, (Module*)App->enemies);
	afflictDmg = App->collisions->AddCollider({ 0, 0, 35, 45 }, Collider::Type::ENEMY_SHOT, (Module*)App->enemies);

}

void Enemy_Dragon::Update() {

	switch (dragonState)
	{
	case Enemy_Dragon::state::FLY:
		position = spawnPos + path.GetRelativePosition();
		currentAnim = path.GetCurrentAnimation();
		path.Update();
		if (position.x <= App->render->camera.x + 20) {
			dragonState = state::ATTACK;
			spawnPos.x = position.x;
			spawnPos.y = position.y;
		}
		break;
	case Enemy_Dragon::state::ATTACK:
		position = spawnPos + attackPath.GetRelativePosition();
		path.relativePosition = attackPath.relativePosition;
		currentAnim = attackPath.GetCurrentAnimation();
		UpdatePath();
		attackPath.Update();
		break;
	case Enemy_Dragon::state::DEAD:
		position = spawnPos + deathPath.GetRelativePosition();
		path.relativePosition = deathPath.relativePosition;
		currentAnim = deathPath.GetCurrentAnimation();
		frame++;
		deathPath.Update();
		if (frame >= 100) {
			SetToDelete();
		}
		break;
	case Enemy_Dragon::state::REPOSITION:
		position = spawnPos + repositionPath.GetRelativePosition();
		path.relativePosition = repositionPath.relativePosition;
		currentAnim = repositionPath.GetCurrentAnimation();
		repositionPath.Update();
		App->collisions->RemoveCollider(receiveDmg);
		if (position.y <= -25) {
			SetToDelete();
		}
	}

	Enemy::Update();
	afflictDmg->SetPos(position.x + 5, position.y + 15);

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
	if (col->type == col->PLAYER_ATTACK && touch == true) {
		App->audio->PlayFx(destroyedFx);
		App->player->score += 100;
		App->collisions->RemoveCollider(afflictDmg);
		touch = false;
		dragonState = state::DEAD;
		spawnPos.x = position.x;
		spawnPos.y = position.y;
	}

	if (App->player->damaged) {
		spawnPos.x = position.x;
		spawnPos.y = position.y;
		dragonState = state::REPOSITION;
	}
}

void Enemy_Dragon::SetToDelete() {
	pendingToDelete = true;
	if (receiveDmg != nullptr)
		receiveDmg->pendingToDelete = true;
	if (afflictDmg != nullptr)
		afflictDmg->pendingToDelete = true;
}