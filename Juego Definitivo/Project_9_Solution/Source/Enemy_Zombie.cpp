#include "Enemy_Zombie.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Zombie::Enemy_Zombie(int x, int y) : Enemy(x,y) {

	// Walk animation
	walking.PushBack({ 3, 8, 30, 60 });
	walking.PushBack({ 47, 9, 30, 60 });
	walking.speed = 0.05f;
	currentAnim = &walking;

	// Explosion animation
	exploding.PushBack({ 172, 11, 30, 60 });
	exploding.PushBack({ 172, 11, 30, 60 });
	exploding.PushBack({ 172, 11, 30, 60 });
	exploding.PushBack({ 172, 11, 30, 60 });
	exploding.PushBack({ 7, 82, 38, 42 });
	exploding.PushBack({ 68, 88, 34, 40 });
	exploding.PushBack({ 124, 82, 33, 45 });

	path.PushBack({ -0.2f, 0.0f }, 150, &walking);

	collider = App->collisions->AddCollider({ 0, 0, 26, 55 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Zombie::Update() {

	//path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	Enemy::Update();
}

void Enemy_Zombie::OnCollision(Collider* collider) {
	if (collider->type == collider->PLAYER) {
		currentAnim = &exploding;
	}
}