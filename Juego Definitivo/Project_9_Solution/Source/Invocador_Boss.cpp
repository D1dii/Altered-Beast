#include "Invocador_Boss.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleRender.h"
#include "SceneLevel1.h"

Invocador_Boss::Invocador_Boss(int x, int y) : Enemy(x, y) {

	//idle
	idleAnim.PushBack({ 191 - 79, 84 - 75, 79, 75 });
	currentAnim = &idleAnim;

	// invocar Boss
	invocarBoss.PushBack({ 191 - 79, 84 - 75, 79, 75 });
	invocarBoss.PushBack({ 88 - 79, 84 - 75, 79, 75 });
	invocarBoss.speed = 0.2f;

	receiveDmg = App->collisions->AddCollider({ position.x - 70, 0, 10, 240 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Invocador_Boss::Update() {

	switch (invocadorState)
	{
	case Invocador_Boss::state::IDLE:
		currentAnim = &idleAnim;
		idleAnim.Update();
		break;
	case Invocador_Boss::state::INVOCAR:
		currentAnim = &invocarBoss;
		invocarBoss.Update();
		frame++;
		if (frame >= 30) {
			App->enemies->AddEnemy(Enemy_Type::BOSS, App->render->camera.x + 180, 65);
			App->sceneLevel_1->isBoss = true;
			SetToDelete();
		}
		break;
	}
}

void Invocador_Boss::OnCollision(Collider* col) {

	if (col->type == col->PLAYER && App->player->phase >= 3) {
		invocadorState = state::INVOCAR;
	}

}

void Invocador_Boss::SetToDelete() {
	pendingToDelete = true;
	if (receiveDmg != nullptr)
		receiveDmg->pendingToDelete = true;
	if (afflictDmg != nullptr)
		afflictDmg->pendingToDelete = true;
}