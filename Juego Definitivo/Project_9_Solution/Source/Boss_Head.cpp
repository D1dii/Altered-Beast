#include "Boss_Head.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "stdio.h"
#include "stdlib.h"
#include <iostream>
#include <random>
#include <chrono>
#include "Windows.h"

Boss_Head::Boss_Head(int x, int y) : Enemy(x, y) {

	// Launch Animation
	launchAnim.PushBack({ 150, 372, 46, 47 });
	currentAnim = &launchAnim;

	// Attack animation
	attackAnim.PushBack({ 204, 354, 46, 47 });

	// Death animation
	deathAnim.PushBack({ 200, 403, 54, 44 });
	deathAnim.PushBack({ 199, 458, 54, 44 });
	deathAnim.PushBack({ 203, 510, 54, 44 });
	deathAnim.speed = 0.1f;

	LaunchPath.PushBack({ -2.0f, -0.75f }, 30, &launchAnim);
	attackPath.PushBack({ 0.0f, 1.5f }, 30, &attackAnim);

	receiveDmg = App->collisions->AddCollider({ position.x - 4, position.y - 3, 50, 50 }, Collider::Type::ENEMY, (Module*)App->enemies);
	afflictDmg = App->collisions->AddCollider({ position.x + 5, position.y + 5, 35, 35 }, Collider::Type::ENEMY_SHOT, (Module*)App->enemies);

}

void Boss_Head::Update() {

	std::mt19937_64 generator;

	unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	generator.seed(seed);

	std::uniform_int_distribution<int> distribution(30, 900);

	int random_number = distribution(generator);

	switch (headState)
	{
	case Boss_Head::state::LAUNCH:
		currentAnim = &launchAnim;
		launchAnim.Update();
		frame++;
		LaunchPath.Update();
		position = spawnPos + LaunchPath.GetRelativePosition();
		if (frame >= random_number) {
			frame = 0;
			spawnPos.x = position.x;
			spawnPos.y = position.y;
			headState = state::ATTACK;
		}
		break;
	case Boss_Head::state::ATTACK:
		currentAnim = &attackAnim;
		attackAnim.Update();
		attackPath.Update();
		position = spawnPos + attackPath.GetRelativePosition();
		break;
	case Boss_Head::state::DEATH:
		currentAnim = &deathAnim;
		deathAnim.Update();
		deathFrame++;
		if (deathFrame >= 15) {
			SetToDelete();
		}
		break;
	
	}

	if (App->player->score >= 1000000) {
		SetToDelete();
	}

	
	receiveDmg->SetPos(position.x - 4, position.y - 3);
	afflictDmg->SetPos(position.x + 5, position.y + 5);

}

void Boss_Head::OnCollision(Collider* col) {
	if (col->type == col->PLAYER_ATTACK && touch == true) {
		headState = state::DEATH;
		//App->collisions->RemoveCollider(afflictDmg);
	}

	if (col->type == col->WALL || App->player->damaged == true) {
		headState = state::DEATH;
		//App->collisions->RemoveCollider(afflictDmg);
	}
}

void Boss_Head::SetToDelete() {
	pendingToDelete = true;
	if (receiveDmg != nullptr)
		receiveDmg->pendingToDelete = true;
	if (afflictDmg != nullptr)
		afflictDmg->pendingToDelete = true;
}