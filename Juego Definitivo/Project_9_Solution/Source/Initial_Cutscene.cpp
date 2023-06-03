#include "Initial_Cutscene.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"

Initial_Cutscene::Initial_Cutscene(int x, int y) : Enemy(x, y) {

	// Initial animation
	
	sceneAnim.speed = 0.2f;
	currentAnim = &sceneAnim;

	

}

void Initial_Cutscene::Update() {
	frame++;
	sceneAnim.Update();

	if (frame == 190) {
		App->player->LevelFinished = true;
		App->audio->PlayFx(LaughFx);
	}

	if (frame >= 550) {
		SetToDelete();
	}

}

void Initial_Cutscene::OnCollision(Collider* col) {

}

void Initial_Cutscene::SetToDelete() {
	pendingToDelete = true;
	if (receiveDmg != nullptr)
		receiveDmg->pendingToDelete = true;
	if (afflictDmg != nullptr)
		afflictDmg->pendingToDelete = true;
}