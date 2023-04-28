#include "Enemy_Zombie.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"

Enemy_Zombie::Enemy_Zombie(int x, int y) : Enemy(x,y) {

	// Walk animation
	walking.PushBack({ 3, 8, 30, 60 });
	walking.PushBack({ 47, 9, 30, 60 });
	walking.speed = 0.05f;
	currentAnim = &walking;

	// Explosion animation
	exploding.PushBack({ 172, 11, 30, 60 });
	exploding.PushBack({ 3, 8, 30, 60 });
	exploding.PushBack({ 172, 11, 30, 60 });
	exploding.PushBack({ 3, 8, 30, 60 });
	exploding.PushBack({ 172, 11, 30, 60 });
	exploding.PushBack({ 3, 8, 30, 60 });
	
	exploding.PushBack({ 7, 82, 38, 42 });
	exploding.PushBack({ 68, 88, 34, 40 });
	exploding.PushBack({ 124, 82, 33, 45 });
	exploding.speed = 0.05f;

	path.PushBack({ -0.2f, 0.0f }, 150, &walking);

	collider = App->collisions->AddCollider({ 0, 0, 26, 55 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Zombie::Update() {

	//path.Update();
	position = spawnPos + path.GetRelativePosition();

	if (zombieState == state::EXPLOSION) {
		
		currentAnim = &exploding;
		exploding.Update();
		frame++;
		if (frame >= 150) {
			App->audio->PlayFx(destroyedFx);
			SetToDelete();
		}

	}
	//currentAnim = path.GetCurrentAnimation();

	Enemy::Update();
}

void Enemy_Zombie::OnCollision(Collider* col) {
	
	if (col->type == col->PLAYER_ATTACK) {
		App->particles->AddParticle(App->particles->explosion, position.x, position.y);
		App->audio->PlayFx(destroyedFx);
		SetToDelete();
	}
	else if (col->type == col->PLAYER) {
		zombieState = state::EXPLOSION;
	}

	
}

void Enemy_Zombie::SetToDelete() {
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}
	
