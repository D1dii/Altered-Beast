#include "Spirit_Ball.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

Spirit_Ball::Spirit_Ball(int x, int y) : Enemy(x, y) {

	// idle
	idle.PushBack({ 27, 21, 16, 17});
	currentAnim = &idle;

	path.PushBack({ -0.3f, 0.0f }, 150, &idle);
	path.PushBack({ 0.3f, 0.0f }, 150, &idle);

	collider = App->collisions->AddCollider({ 0, 0, 16, 17 }, Collider::Type::ITEM, (Module*)App->enemies);
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
	if (collider != nullptr)
		collider->pendingToDelete = true;
}