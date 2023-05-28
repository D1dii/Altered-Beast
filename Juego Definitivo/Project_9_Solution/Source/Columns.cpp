#include "Columns.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

Columns::Columns(int x, int y) : Enemy(x, y) {

	// idle
	idle.PushBack({ 94, 80, 139 - 94, 168 - 80 });
	idle.speed = 0.1f;

	spawnAnim.PushBack({ 94, 80, 139 - 94, 20 });
	spawnAnim.PushBack({ 94,80, 139 - 94, 40 });
	spawnAnim.PushBack({ 94, 80, 139 - 94, 60 });
	spawnAnim.PushBack({ 94, 80, 139 - 94, 168 - 80 });
	spawnAnim.speed = 0.4f;
	shaking.PushBack({ 90, 80, 139 - 94, 168 - 80 });
	shaking.PushBack({ 96, 80, 139 - 94, 168 - 80 });
	shaking.PushBack({ 90, 80, 139 - 94, 168 - 80 });
	shaking.PushBack({ 96, 80, 139 - 94, 168 - 80 });
	shaking.speed = 0.5f;

	receiveDmg = App->collisions->AddCollider({ 0, 0, 139 - 94, 168 - 80 }, Collider::Type::COLUMNS, (Module*)App->enemies);
}

void Columns::Update()
{
	position = spawnPos;

	//Spawning Columns
	if (App->player->position.x >= spawnPos.x - 200 && App->player->position.x <= spawnPos.x - 180)
	{
		currentAnim = &spawnAnim;
		frame++;
		if (frame > 10)
		{
			currentAnim = &idle;
		}
		//currentAnim = &idle;
	}



	Enemy::Update();
}

void Columns::OnCollision(Collider* col)
{
	if (col->type == col->PLAYER_ATTACK)
	{
		currentAnim = &shaking;
		frame++;
		if (frame >= 20) {
			SetToDelete();
		}

	}
	else if (col->type == col->PLAYER)
	{
		//App->player->position.y -= 60;
	}
}

void Columns::SetToDelete() {
	pendingToDelete = true;
	if (receiveDmg != nullptr)
		receiveDmg->pendingToDelete = true;
}