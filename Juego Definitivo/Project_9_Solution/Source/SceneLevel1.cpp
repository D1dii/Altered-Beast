#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgbackTexture = App->textures->Load("Assets/Sprites/backbg.png");
	bgfrontTexture = App->textures->Load("Assets/Sprites/frontbg.png");
	zombie = App->textures->Load("Assets/Sprites/Zombie.png");

	App->audio->PlayMusic("Assets/Music/round1.ogg", 1.0f);

	//Bottomside collider
	bgfront = App->collisions->AddCollider({ 0, 217, 1600, 24 }, Collider::Type::WALL);
	bgright = App->collisions->AddCollider({ 320, 0, 10, 240 }, Collider::Type::SCREEN_RIGHT);
	bgleft = App->collisions->AddCollider({ 0, 0, 10, 240 }, Collider::Type::SCREEN_LEFT);

	//First two columns colliders
	App->collisions->AddCollider({ 1375, 0, 111, 96 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1375, 145, 111, 96 }, Collider::Type::WALL);

	// Enemies ---
	
	App->enemies->AddEnemy(Enemy_Type::ZOMBIE, 200, 158);

	App->enemies->AddEnemy(Enemy_Type::MECH, 900, 195);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->Enable();
	App->enemies->Enable();

	return ret;
}

Update_Status SceneLevel1::Update()
{
	App->render->camera.x += 1;
	bgleft->SetPos(App->render->camera.x * 0.334, 0);
	bgright->SetPos(App->render->camera.x * 0.334 + 310, 0);

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgbackTexture, 0, 0, NULL, 0.6f);
	App->render->Blit(bgfrontTexture, 0, 187, NULL, 0.7f);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();
	App->collisions->RemoveCollider(App->player->collider);
	App->collisions->RemoveCollider(bgleft);
	App->collisions->RemoveCollider(bgright);
	App->collisions->RemoveCollider(bgfront);

	// TODO 5 (old): Remove All Memory Leaks - no solution here guys ;)

	return true;
}