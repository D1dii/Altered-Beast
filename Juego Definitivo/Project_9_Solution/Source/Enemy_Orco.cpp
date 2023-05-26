#include "Enemy_Orco.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

Enemy_Orco::Enemy_Orco(int x, int y) : Enemy(x, y){

	// Walk animation
	walking.PushBack({ 41, 13, 51, 70 });
	walking.PushBack({ 93, 12, 42, 71 });
	walking.PushBack({ 136, 10, 43, 70 });
	walking.speed = 0.1f;

	// Idle

	idle.PushBack({ 151, 97, 44, 70 });

	// Punch animation
	punchOrco.PushBack({ 3, 99, 63, 70 });
	punchOrco.PushBack({ 272, 11, 62, 70 });
	punchOrco.PushBack({ 151, 97, 44, 70 });
	punchOrco.speed = 0.1f;

	// Hit animation
	Hit.PushBack({ 86, 101, 45, 62 });

	// Death animation (same as hit)
	death.PushBack({ 86, 101, 45, 62 });

	path.PushBack({ -0.1f, 0.0f }, 150, &walking);

	receiveDmg = App->collisions->AddCollider({ position.x - 10, position.y - 10, 40, 70 }, Collider::Type::ENEMY, (Module*)App->enemies);
	punchAttack = App->collisions->AddCollider({ 0, 0, 0, 0 }, Collider::Type::ENEMY_SHOT, (Module*)App->enemies);
	afflictDmg = App->collisions->AddCollider({ 0, 0, 16, 40 }, Collider::Type::ENEMY_SHOT, (Module*)App->enemies);

}

void Enemy_Orco::Update() {

	position = spawnPos + path.GetRelativePosition();

	switch (orcoState)
	{
	case Enemy_Orco::state::WALK:
		currentAnim = &walking;
		walking.Update();
		path.Update();
		break;
	case Enemy_Orco::state::HIT:
		currentAnim = &Hit;
		Hit.Update();
		frame++;
		if (frame >= 30) {
			orcoState = state::WALK;
			touch = true;
			frame = 0;
		}
		break;
	case Enemy_Orco::state::PUNCH_ORCO:
		punchFrame++;
		punchAttack->SetPos(position.x - 5, position.y + 5);
		punchAttack->rect.w = 30;
		punchAttack->rect.h = 15;
		if (punchFrame <= 15) {
			currentAnim = &punchOrco;
			punchOrco.Update();
		}
		else if (punchFrame > 15 && punchFrame <= 25) {
			punchAttack->SetPos(position.x - 5, -20);
			currentAnim = &idle;
			idle.Update();
		}
		else if (punchFrame > 25) {
			orcoState = state::WALK;
			punchFrame = 0;
		}
		break;
	case Enemy_Orco::state::DEATH:
		currentAnim = &death;
		death.Update();
		frame++;
		if (frame >= 15) {
			SetToDelete();
		}
		break;
	}

	Enemy::Update();
	afflictDmg->SetPos(position.x + 20, position.y + 7);
	receiveDmg->SetPos(position.x + 10, position.y - 10);
}

void Enemy_Orco::OnCollision(Collider* col) {
	if (col->type == col->PLAYER_ATTACK && touch == true) {
		orcoState = state::HIT;
		touch = false;
		life -= App->player->damage;
		if (life <= 0) {
			orcoState = state::DEATH;
			App->audio->PlayFx(destroyedFx);
			App->player->score += 300;
			App->collisions->RemoveCollider(punchAttack);
		}
	}

	if (col->type == col->PLAYER) {
		orcoState = state::PUNCH_ORCO;
	}
}

void Enemy_Orco::SetToDelete() {
	pendingToDelete = true;
	if (receiveDmg != nullptr)
		receiveDmg->pendingToDelete = true;
	if (afflictDmg != nullptr)
		afflictDmg->pendingToDelete = true;
}