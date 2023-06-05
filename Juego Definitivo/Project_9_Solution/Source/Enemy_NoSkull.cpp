#include "Enemy_NoSkull.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "SceneLevel1.h"

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

	receiveDmg = App->collisions->AddCollider({ position.x - 10, position.y - 10, 40, 70 }, Collider::Type::ENEMY, (Module*)App->enemies);
	punchAttack = App->collisions->AddCollider({ 0, 0, 0, 0 }, Collider::Type::ENEMY_SHOT, (Module*)App->enemies);
	afflictDmg = App->collisions->AddCollider({ 0, 0, 16, 40 }, Collider::Type::ENEMY_SHOT, (Module*)App->enemies);

}

void Enemy_NoSkull::Update() {

	if (App->sceneLevel_1->isBoss == true || App->player->restartLevel == true) {
		SetToDelete();
	}

	position = spawnPos + path.GetRelativePosition();

	switch (zombieState) {
	case state::WALK:
		currentAnim = &walking;
		walking.Update();
		path.Update();
		break;
	case state::PUNCH_ZOMBIE:
		punchFrame++;
		punchAttack->SetPos(position.x, position.y - 5);
		punchAttack->rect.w = 30;
		punchAttack->rect.h = 15;
		if (punchFrame <= 15) {
			currentAnim = &punchZombie;
			punchZombie.Update();
		}
		else if (punchFrame > 15) {
			punchAttack->SetPos(position.x, -20);
			zombieState = state::WALK;
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



	
	afflictDmg->SetPos(position.x + 5, position.y + 7);
	receiveDmg->SetPos(position.x - 10, position.y - 10);
}

void Enemy_NoSkull::OnCollision(Collider* col) {

	if (col->type == col->PLAYER_ATTACK && zombieState == state::WALK && touch == true) {
		currentAnim = &firstHit;
		touch = false;
		life -= App->player->damage;
		if (life <= 0) {
			App->audio->PlayFx(destroyedFx);
			App->player->score += 100;
			App->collisions->RemoveCollider(afflictDmg);
			SetToDelete();
		}
		else {
			zombieState = state::WALK_2;
		}

	}
	
	if (col->type == col->PLAYER_ATTACK && zombieState == state::WALK_2 && touch == true) {
		App->audio->PlayFx(destroyedFx);
		App->player->score += 100;
		App->collisions->RemoveCollider(afflictDmg);
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
	if (receiveDmg != nullptr)
		receiveDmg->pendingToDelete = true;
	if (afflictDmg != nullptr)
		afflictDmg->pendingToDelete = true;
}
