#include "cnt_Initial_Cutscene.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"

cnt_Initial_Cutscene::cnt_Initial_Cutscene(int x, int y) : Enemy(x, y) {

	// Final animation
	sceneAnim.PushBack({ 0, 0, 320, 224 });
	sceneAnim.PushBack({ 320, 0, 320, 224 });
	sceneAnim.PushBack({ 640, 0, 320, 224 });
	sceneAnim.PushBack({ 1300, 0, 320, 224 });
	sceneAnim.PushBack({ 1620, 0, 320, 224 });
	sceneAnim.PushBack({ 1940, 0, 320, 224 });
	sceneAnim.PushBack({ 2260, 0, 320, 224 });
	sceneAnim.PushBack({ 2580, 0, 320, 224 });
	sceneAnim.PushBack({ 2900, 0, 320, 224 });
	sceneAnim.PushBack({ 3320, 0, 320, 224 });
	sceneAnim.PushBack({ 3540, 0, 320, 224 });
	sceneAnim.PushBack({ 4180, 0, 320, 224 });
	sceneAnim.PushBack({ 4500, 0, 320, 224 });
	sceneAnim.PushBack({ 4820, 0, 320, 224 });
	sceneAnim.PushBack({ 0, 224, 320, 224 });
	sceneAnim.PushBack({ 320, 224, 320, 224 });
	sceneAnim.PushBack({ 0, 448, 320, 224 });
	sceneAnim.PushBack({ 320, 448, 320, 224 });
	sceneAnim.PushBack({ 640, 448, 320, 224 });
	sceneAnim.PushBack({ 1300, 448, 320, 224 });
	sceneAnim.PushBack({ 1620, 448, 320, 224 });
	sceneAnim.PushBack({ 1940, 448, 320, 224 });
	sceneAnim.PushBack({ 2260, 448, 320, 224 });
	sceneAnim.PushBack({ 2580, 448, 320, 224 });
	sceneAnim.PushBack({ 2900, 448, 320, 224 });
	sceneAnim.PushBack({ 3320, 448, 320, 224 });
	sceneAnim.PushBack({ 3540, 448, 320, 224 });
	sceneAnim.PushBack({ 0, 672, 320, 224 });
	sceneAnim.PushBack({ 320, 672, 320, 224 });
	sceneAnim.PushBack({ 0, 896, 320, 224 });
	sceneAnim.PushBack({ 320, 896, 320, 224 });
	sceneAnim.PushBack({ 640, 896, 320, 224 });
	sceneAnim.PushBack({ 1300, 896, 320, 224 });
	sceneAnim.PushBack({ 1620, 896, 320, 224 });
	sceneAnim.PushBack({ 1940, 896, 320, 224 });
	sceneAnim.PushBack({ 2260, 896, 320, 224 });
	sceneAnim.PushBack({ 2580, 896, 320, 224 });
	sceneAnim.PushBack({ 2900, 896, 320, 224 });
	sceneAnim.PushBack({ 3320, 896, 320, 224 });
	sceneAnim.PushBack({ 3540, 896, 320, 224 });
	sceneAnim.PushBack({ 4180, 896, 320, 224 });
	sceneAnim.PushBack({ 4500, 896, 320, 224 });
	sceneAnim.PushBack({ 4820, 896, 320, 224 });
	sceneAnim.PushBack({ 0, 1120, 320, 224 });
	sceneAnim.PushBack({ 320, 1120, 320, 224 });
	sceneAnim.speed = 0.2f;
	currentAnim = &sceneAnim;

	RiseFx = App->audio->LoadFx("Assets/Fx/rise.ogg");

}

void cnt_Initial_Cutscene::Update() {
	frame++;
	sceneAnim.Update();

	if (frame >= 15 && frame < 125) {
		if (frame >= 34) {
			App->audio->PlayFx(RiseFx);
		}
		if (frame % 2 == 0) {
			sceneAnim.PushBack({ 320, 224, 320, 224 });
		}
		else {
			sceneAnim.PushBack({ 0, 224, 320, 224 });
		}
	}

	if (frame >= 155 && frame <= 188) {
		if (frame % 2 == 1) {
			sceneAnim.PushBack({ 0, 672, 320, 224 });
		}
		else {
			sceneAnim.PushBack({ 320, 672, 320, 224 });
		}
	}



	if (frame >= 206) {
		SetToDelete();
	}

}

void cnt_Initial_Cutscene::OnCollision(Collider* col) {

}

void cnt_Initial_Cutscene::SetToDelete() {
	pendingToDelete = true;
	if (receiveDmg != nullptr)
		receiveDmg->pendingToDelete = true;
	if (afflictDmg != nullptr)
		afflictDmg->pendingToDelete = true;
}