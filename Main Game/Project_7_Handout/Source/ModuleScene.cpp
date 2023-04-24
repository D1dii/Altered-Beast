#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"

ModuleScene::ModuleScene()
{

}

ModuleScene::~ModuleScene()
{

}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgbackTexture = App->textures->Load("Assets/backbg.png");
	bgfrontTexture = App->textures->Load("Assets/frontbg.png");
	
	App->audio->PlayMusic("Assets/round1.ogg", 1.0f);

	//Bottomside collider
	bgfront = App->collisions->AddCollider({ 0, 217, 1600, 24}, Collider::Type::WALL);
	bgright = App->collisions->AddCollider({ 374, 0, 10, 240}, Collider::Type::SCREEN_RIGHT);
	bgleft = App->collisions->AddCollider({ 0, 0, 10, 240}, Collider::Type::SCREEN_LEFT);
	

	//First two columns colliders
	App->collisions->AddCollider({ 1375, 0, 111, 96 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1375, 145, 111, 96 }, Collider::Type::WALL);


	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 600, 80);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 625, 80);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 640, 80);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 665, 80);

	// TODO 1: Add a new wave of red birds
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 900, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 925, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 940, 100);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 965, 100);

	// TODO 2: Add a new wave of brown cookies
	App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 1200, 65);
	App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 1225, 65);
	App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 1240, 65);
	App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 1265, 65);

	// TODO 4: Create a new enemy type: The Mech


	return ret;
}

update_status ModuleScene::Update()
{
	App->render->camera.x += 1;
	bgleft->SetPos(App->render->camera.x*0.334, 0);
	bgright->SetPos(App->render->camera.x*0.334+ 374, 0);
	


	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgbackTexture, 0, 0, NULL, 0.6f);
	App->render->Blit(bgfrontTexture, 0, 187, NULL, 0.7f);

	return update_status::UPDATE_CONTINUE;
}