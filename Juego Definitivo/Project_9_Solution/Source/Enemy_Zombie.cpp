#include "Enemy_Zombie.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

Enemy_Zombie::Enemy_Zombie(int x, int y) : Enemy(x,y) {

	// Walk animation
	walking.PushBack({ 3, 8, 30, 64 });
	walking.PushBack({ 47, 9, 30, 64 });
	walking.speed = 0.05f;
	currentAnim = &walking;

	// Walk without head
	noHead.PushBack({ 132, 9, 30, 64 });
	noHead.PushBack({ 206, 81, 30, 64 });
	noHead.speed = 0.05f;

	// Hit
	firstHit.PushBack({ 92, 5, 30, 64 });

	// Explosion with Head animation
	headExplosion.PushBack({ 211, 9, 30, 60 });
	headExplosion.PushBack({ 47, 9, 30, 60 });
	headExplosion.PushBack({ 211, 9, 30, 60 });
	headExplosion.PushBack({ 47, 9, 30, 60 });
	headExplosion.PushBack({ 211, 9, 30, 60 });
	headExplosion.PushBack({ 47, 9, 30, 60 });
	
	headExplosion.PushBack({ 7, 82, 38, 42 });
	headExplosion.PushBack({ 68, 88, 34, 40 });
	headExplosion.PushBack({ 124, 82, 33, 45 });
	headExplosion.PushBack({ 7, 82, 38, 42 });
	headExplosion.PushBack({ 68, 88, 34, 40 });
	headExplosion.PushBack({ 124, 82, 33, 45 });
	headExplosion.speed = 0.05f;

	// Explosion without Head animation
	noHeadExplosion.PushBack({ 171, 9, 30, 60 });
	noHeadExplosion.PushBack({ 132, 9, 30, 64 });
	noHeadExplosion.PushBack({ 171, 9, 30, 60 });
	noHeadExplosion.PushBack({ 132, 9, 30, 64 });
	noHeadExplosion.PushBack({ 171, 9, 30, 60 });
	noHeadExplosion.PushBack({ 132, 9, 30, 64 });

	noHeadExplosion.PushBack({ 7, 82, 38, 42 });
	noHeadExplosion.PushBack({ 68, 88, 34, 40 });
	noHeadExplosion.PushBack({ 124, 82, 33, 45 });
	noHeadExplosion.PushBack({ 7, 82, 38, 42 });
	noHeadExplosion.PushBack({ 68, 88, 34, 40 });
	noHeadExplosion.PushBack({ 124, 82, 33, 45 });
	noHeadExplosion.speed = 0.05f;

	path.PushBack({ -0.15f, 0.0f }, 150, &walking);

	collider = App->collisions->AddCollider({ 0, 0, 26, 55 }, Collider::Type::ENEMY, (Module*)App->enemies);
	explosion = App->collisions->AddCollider({ 0, 0, 0, 0 }, Collider::Type::ENEMY_SHOT, (Module*)App->enemies);
	
}

void Enemy_Zombie::Update() {

	
	position = spawnPos + path.GetRelativePosition();

	switch (zombieState) {
	case state::WALK:
		currentAnim = &walking;
		walking.Update();
		path.Update();
		break;
	case state::EXPLOSIONHEAD:
		currentAnim = &headExplosion;
		headExplosion.Update();
		frame++;
		if (frame >= 60 && frame < 90) {
			headExplosion.speed = 0.1f;
		}
		else if (frame == 90) {
			explosion->SetPos(position.x - 20, position.y);
			explosion->rect.w = 30;
			explosion->rect.h = 50;
		}
		else if (frame > 90) {
			App->audio->PlayFx(destroyedFx);
			App->collisions->RemoveCollider(explosion);
			SetToDelete();
		}
		break;
	case state::NO_HEAD:
		frame++;
		path.Update();
		if (frame <= 20) {
			currentAnim = &firstHit;
			firstHit.Update();
			
		}
		else if (frame > 20) {
			currentAnim = &noHead;
			noHead.Update();
			touch = true;
		}
		break;
	case state::EXPLOSION_NO_HEAD:
		currentAnim = &noHeadExplosion;
		noHeadExplosion.Update();
		frame++;
		if (frame >= 60 && frame < 90) {
			noHeadExplosion.speed = 0.1f;
		}
		else if (frame == 90) {
			explosion->SetPos(position.x - 20, position.y);
			explosion->rect.w = 30;
			explosion->rect.h = 50;
		}
		else if (frame > 90) {
			App->audio->PlayFx(destroyedFx);
			SetToDelete();
			App->collisions->RemoveCollider(explosion);
		}
		break;
	}

	

	Enemy::Update();
}

void Enemy_Zombie::OnCollision(Collider* col) {
	
	if (col->type == col->PLAYER_ATTACK && zombieState == state::WALK) {
		currentAnim = &firstHit;
		zombieState = state::NO_HEAD;
		touch = false;
		
	}
	else if (col->type == col->PLAYER_ATTACK && zombieState == state::NO_HEAD && touch == true) {
		App->audio->PlayFx(destroyedFx);
		App->player->score += 100;
		SetToDelete();
	}
	else if (col->type == col->PLAYER && zombieState == state::WALK) {
		zombieState = state::EXPLOSIONHEAD;
	}
	else if (col->type == col->PLAYER && zombieState == state::NO_HEAD) {
		frame = 0;
		zombieState = state::EXPLOSION_NO_HEAD;
	}

	
}

void Enemy_Zombie::SetToDelete() {
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}
	
