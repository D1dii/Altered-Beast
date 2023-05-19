#include "Spirit_Ball.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

Spirit_Ball::Spirit_Ball(int x, int y) : Enemy(x, y) {

	// idle
	idle.PushBack({ 326, 26, 18, 14});
	idle.PushBack({ 358, 27, 18, 14 });
	idle.PushBack({ 387, 26, 18, 14 });
	idle.speed = 0.1f;
	currentAnim = &idle;

	path.PushBack({ -0.5f, 0.0f }, 75, &idle);
	path.PushBack({ 1.5f, 0.0f }, 75, &idle);

	receiveDmg = App->collisions->AddCollider({ 0, 0, 16, 17 }, Collider::Type::ITEM, (Module*)App->enemies);
}

void Spirit_Ball::Update() {
	position = spawnPos + path.GetRelativePosition();
	path.Update();
	currentAnim = path.GetCurrentAnimation();


	Enemy::Update();
}

void Spirit_Ball::OnCollision(Collider* col) {
	if (col->type == col->PLAYER) {
		SetToDelete();
	}
}

void Spirit_Ball::SetToDelete() {
	pendingToDelete = true;
	if (receiveDmg != nullptr)
		receiveDmg->pendingToDelete = true;
}