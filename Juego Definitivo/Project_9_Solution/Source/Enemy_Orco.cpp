#include "Enemy_Orco.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

Enemy_Orco::Enemy_Orco(int x, int y) : Enemy(x, y){

	// Walk animation
	walking.PushBack({ 57, 13, 35, 70 });
	walking.PushBack({ 112, 12, 23, 71 });
	walking.PushBack({ 145, 10, 34, 70 });
	walking.speed = 0.1f;

	// Idle

	idle.PushBack({ 112, 12, 23, 71 });

	// Punch animation
	punchOrco.PushBack({ 3, 99, 63, 70 });
	punchOrco.PushBack({ 272, 11, 62, 70 });
	punchOrco.PushBack({ 151, 97, 44, 70 });
	punchOrco.PushBack({ 198, 13, 58, 70 });
	punchOrco.speed = 0.05f;

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
		punchAttack->SetPos(position.x - 15, position.y);
		punchAttack->rect.w = 30;
		punchAttack->rect.h = 15;
		if (punchFrame <= 40) {
			currentAnim = &punchOrco;
			punchOrco.Update();
		}
		else if (punchFrame > 40 && punchFrame <= 50) {
			App->collisions->RemoveCollider(punchAttack);
			currentAnim = &idle;
			idle.Update();
		}
		else if (punchFrame > 50) {
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
	afflictDmg->SetPos(position.x + 5, position.y + 7);
	receiveDmg->SetPos(position.x - 10, position.y - 10);
}

void Enemy_Orco::OnCollision(Collider* col) {
	if (col->type == col->PLAYER_ATTACK && touch == true && life > 0) {
		orcoState = state::HIT;
		touch = false;
		life--;
	}

	if (col->type == col->PLAYER_ATTACK && touch == true && life <= 0) {
		orcoState = state::DEATH;
		App->player->score += 300;
		touch = false;
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