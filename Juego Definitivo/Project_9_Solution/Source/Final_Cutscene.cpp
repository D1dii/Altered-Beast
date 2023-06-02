#include "Final_Cutscene.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"

Final_Cutscene::Final_Cutscene(int x, int y) : Enemy(x, y) {

	// Final animation
	sceneAnim.PushBack({21, 0, 290, 225});
	sceneAnim.PushBack({ 341, 0, 290, 225 });
	sceneAnim.PushBack({ 661, 0, 290, 225 });
	sceneAnim.PushBack({ 1301, 0, 290, 225 });
	sceneAnim.PushBack({ 1621, 0, 290, 225 });
	sceneAnim.PushBack({ 1941, 0, 290, 225 });
	sceneAnim.PushBack({ 2261, 0, 290, 225 });
	sceneAnim.PushBack({ 2581, 0, 290, 225 });
	sceneAnim.PushBack({ 2901, 0, 290, 225 });
	sceneAnim.PushBack({ 3221, 0, 290, 225 });
	sceneAnim.PushBack({ 3541, 0, 290, 225 });
	sceneAnim.PushBack({ 3861, 0, 290, 225 });
	sceneAnim.PushBack({ 4181, 0, 290, 225 });
	sceneAnim.PushBack({ 4501, 0, 290, 225 });
	sceneAnim.PushBack({ 21, 222, 290, 225 });
	sceneAnim.PushBack({ 341, 222, 290, 225 });
	sceneAnim.PushBack({ 661, 222, 290, 225 });
	sceneAnim.PushBack({ 1301, 222, 290, 225 });
	sceneAnim.PushBack({ 1621, 222, 290, 225 });
	sceneAnim.PushBack({ 1941, 222, 290, 225 });
	sceneAnim.PushBack({ 2261, 222, 290, 225 });
	sceneAnim.PushBack({ 2581, 222, 290, 225 });
	sceneAnim.PushBack({ 2901, 222, 290, 225 });
	sceneAnim.PushBack({ 3221, 222, 290, 225 });
	sceneAnim.PushBack({ 3541, 222, 290, 225 });
	sceneAnim.PushBack({ 3861, 222, 290, 225 });
	sceneAnim.PushBack({ 4181, 222, 290, 225 });
	sceneAnim.PushBack({ 4501, 222, 290, 225 });
	sceneAnim.PushBack({ 21, 446, 290, 225 });
	sceneAnim.PushBack({ 341, 446, 290, 225 });
	sceneAnim.PushBack({ 661, 446, 290, 225 });
	sceneAnim.PushBack({ 1301, 446, 290, 225 });
	sceneAnim.PushBack({ 1621, 446, 290, 225 });
	sceneAnim.PushBack({ 1941, 446, 290, 225 });
	sceneAnim.PushBack({ 2261, 446, 290, 225 });
	sceneAnim.PushBack({ 2581, 446, 290, 225 });
	sceneAnim.PushBack({ 2901, 446, 290, 225 });
	sceneAnim.PushBack({ 3221, 446, 290, 225 });
	sceneAnim.PushBack({ 3541, 446, 290, 225 });
	sceneAnim.PushBack({ 3861, 446, 290, 225 });
	sceneAnim.PushBack({ 4181, 446, 290, 225 });
	sceneAnim.PushBack({ 4501, 446, 290, 225 });
	sceneAnim.PushBack({ 21, 670, 290, 225 });
	sceneAnim.PushBack({ 341, 670, 290, 225 });
	sceneAnim.PushBack({ 661, 670, 290, 225 });
	sceneAnim.PushBack({ 1301, 670, 290, 225 });
	sceneAnim.PushBack({ 1621, 670, 290, 225 });
	sceneAnim.PushBack({ 1941, 670, 290, 225 });
	sceneAnim.PushBack({ 2261, 670, 290, 225 });
	sceneAnim.PushBack({ 2581, 670, 290, 225 });
	sceneAnim.PushBack({ 2901, 670, 290, 225 });
	sceneAnim.PushBack({ 3221, 670, 290, 225 });
	sceneAnim.PushBack({ 3541, 670, 290, 225 });
	sceneAnim.PushBack({ 3861, 670, 290, 225 });
	sceneAnim.PushBack({ 4181, 670, 290, 225 });
	sceneAnim.PushBack({ 4501, 670, 290, 225 });
	sceneAnim.PushBack({ 21, 894, 290, 225 });
	sceneAnim.PushBack({ 341, 894, 290, 225 });
	sceneAnim.PushBack({ 661, 894, 290, 225 });
	sceneAnim.PushBack({ 1301, 894, 290, 225 });
	sceneAnim.PushBack({ 1621, 894, 290, 225 });
	sceneAnim.PushBack({ 1941, 894, 290, 225 });
	sceneAnim.PushBack({ 2261, 894, 290, 225 });
	sceneAnim.PushBack({ 2581, 894, 290, 225 });
	sceneAnim.PushBack({ 2901, 894, 290, 225 });
	sceneAnim.PushBack({ 3221, 894, 290, 225 });
	sceneAnim.PushBack({ 3541, 894, 290, 225 });
	sceneAnim.PushBack({ 3861, 894, 290, 225 });
	sceneAnim.PushBack({ 4181, 894, 290, 225 });
	sceneAnim.PushBack({ 4501, 894, 290, 225 });
	sceneAnim.PushBack({ 21, 1118, 290, 225 });
	sceneAnim.PushBack({ 341, 1118, 290, 225 });
	sceneAnim.PushBack({ 661, 1118, 290, 225 });
	sceneAnim.PushBack({ 1301, 1118, 290, 225 });
	sceneAnim.PushBack({ 1621, 1118, 290, 225 });
	sceneAnim.PushBack({ 1941, 1118, 290, 225 });
	sceneAnim.PushBack({ 2261, 1118, 290, 225 });
	sceneAnim.PushBack({ 2581, 1118, 290, 225 });
	sceneAnim.PushBack({ 2901, 1118, 290, 225 });
	sceneAnim.PushBack({ 3221, 1118, 290, 225 });
	sceneAnim.PushBack({ 3541, 1118, 290, 225 });
	sceneAnim.PushBack({ 3861, 1118, 290, 225 });
	sceneAnim.PushBack({ 4181, 1118, 290, 225 });
	sceneAnim.PushBack({ 4501, 1118, 290, 225 });
	sceneAnim.PushBack({ 21, 1342, 290, 225 });
	sceneAnim.PushBack({ 341, 1342, 290, 225 });
	sceneAnim.PushBack({ 661, 1342, 290, 225 });
	sceneAnim.PushBack({ 1301, 1342, 290, 225 });
	sceneAnim.PushBack({ 1621, 1342, 290, 225 });
	sceneAnim.PushBack({ 1941, 1342, 290, 225 });
	sceneAnim.PushBack({ 2261, 1342, 290, 225 });
	sceneAnim.PushBack({ 2581, 1342, 290, 225 });
	sceneAnim.PushBack({ 2901, 1342, 290, 225 });
	sceneAnim.PushBack({ 3221, 1342, 290, 225 });
	sceneAnim.PushBack({ 3541, 1342, 290, 225 });
	sceneAnim.PushBack({ 3861, 1342, 290, 225 });
	sceneAnim.PushBack({ 4181, 1342, 290, 225 });
	sceneAnim.PushBack({ 21, 1567, 290, 225 });
	sceneAnim.PushBack({ 341, 1567, 290, 225 });
	sceneAnim.PushBack({ 661, 1567, 290, 225 });
	sceneAnim.PushBack({ 1301, 1567, 290, 225 });
	sceneAnim.PushBack({ 1621, 1567, 290, 225 });
	sceneAnim.PushBack({ 1941, 1567, 290, 225 });
	sceneAnim.PushBack({ 2261, 1567, 290, 225 });
	sceneAnim.PushBack({ 2581, 1567, 290, 225 });
	sceneAnim.PushBack({ 2901, 1567, 290, 225 });
	sceneAnim.PushBack({ 3221, 1567, 290, 225 });
	sceneAnim.PushBack({ 3541, 1567, 290, 225 });
	sceneAnim.PushBack({ 3861, 1567, 290, 225 });
	sceneAnim.PushBack({ 4181, 1567, 290, 225 });
	sceneAnim.PushBack({ 4501, 1567, 290, 225 });
	sceneAnim.PushBack({ 4501, 1342, 290, 225 });
	sceneAnim.speed = 0.2f;
	currentAnim = &sceneAnim;

	LaughFx = App->audio->LoadFx("Assets/Fx/laughing.ogg");

}

void Final_Cutscene::Update() {
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

void Final_Cutscene::OnCollision(Collider* col) {

}

void Final_Cutscene::SetToDelete() {
	pendingToDelete = true;
	if (receiveDmg != nullptr)
		receiveDmg->pendingToDelete = true;
	if (afflictDmg != nullptr)
		afflictDmg->pendingToDelete = true;
}