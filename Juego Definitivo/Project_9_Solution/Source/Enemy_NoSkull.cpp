#include "Enemy_NoSkull.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

Enemy_NoSkull::Enemy_NoSkull(int x, int y) : Enemy(x, y) {

	// Walk animation
	walking.PushBack({ 18, 11, 30, 62 });
	walking.PushBack({ 67, 13, 30, 62 });
	walking.speed = 0.05f;
	currentAnim = &walking;

	// Hit
	firstHit.PushBack({ 181, 11, 31, 62 });

	// Punch enemy
	punchZombie.PushBack({ 109, 12, 55, 62 });
	

	path.PushBack({ -0.15f, 0.0f }, 150, &walking);

	collider = App->collisions->AddCollider({ 0, 0, 26, 55 }, Collider::Type::ENEMY, (Module*)App->enemies);
	attack = App->collisions->AddCollider({ 0, 0, 0, 0 }, Collider::Type::ENEMY_SHOT, (Module*)App->enemies);

}

void Enemy_NoSkull::Update() {


	position = spawnPos + path.GetRelativePosition();

	switch (zombieState) {
	case state::WALK:
		currentAnim = &walking;
		walking.Update();
		path.Update();
		break;
	case state::PUNCH_ZOMBIE:
		punchFrame++;
		attack->SetPos(position.x, position.y - 5);
		attack->rect.w = 30;
		attack->rect.h = 15;
		if (punchFrame <= 15) {
			currentAnim = &punchZombie;
			punchZombie.Update();
		}
		else if (punchFrame > 15) {
			App->collisions->RemoveCollider(attack);
		}
		break;
	case state::WALK_2:
		frame++;
		path.Update();
		if (frame <= 30) {
			currentAnim = &firstHit;
			firstHit.Update();

		}
		else if (frame > 30) {
			currentAnim = &walking;
			walking.Update();
			touch = true;
		}
		break;
	}



	Enemy::Update();
}

void Enemy_NoSkull::OnCollision(Collider* col) {

	if (col->type == col->PLAYER_ATTACK && zombieState == state::WALK) {
		currentAnim = &firstHit;
		zombieState = state::WALK_2;
		touch = false;

	}
	else if (col->type == col->PLAYER_ATTACK && zombieState == state::WALK_2 && touch == true) {
		App->audio->PlayFx(destroyedFx);
		App->player->score += 100;
		SetToDelete();
	}
	else if (col->type == col->PLAYER && zombieState == state::WALK) {
		zombieState = state::PUNCH_ZOMBIE;
	}
	else if (col->type == col->PLAYER && zombieState == state::WALK_2) {
		frame = 0;
		zombieState = state::PUNCH_ZOMBIE;
	}


}

void Enemy_NoSkull::SetToDelete() {
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}
