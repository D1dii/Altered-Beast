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
	bool onBeastForm = false;

	bgbackTexture = App->textures->Load("Assets/Sprites/backbg.png");
	bgfrontTexture = App->textures->Load("Assets/Sprites/frontbg.png");
	zombie = App->textures->Load("Assets/Sprites/Zombie.png");

	App->audio->PlayMusic("Assets/Music/round1.ogg", 1.0f);

	beastHowl = App->audio->LoadFx("Assets/Fx/howl.ogg");

	//Bottomside collider
	bgfront = App->collisions->AddCollider({ 0, 217, 1600, 24 }, Collider::Type::WALL);
	bgright = App->collisions->AddCollider({ 320, 0, 10, 240 }, Collider::Type::SCREEN_RIGHT);
	bgleft = App->collisions->AddCollider({ 0, 0, 10, 240 }, Collider::Type::SCREEN_LEFT);

	// Enemies ---
	
	App->enemies->AddEnemy(Enemy_Type::NO_SKULL, 400, 156);
	/*App->enemies->AddEnemy(Enemy_Type::ZOMBIE, 800, 158);
	App->enemies->AddEnemy(Enemy_Type::WOLF, 1200, 177);
	App->enemies->AddEnemy(Enemy_Type::WOLF_BLUE, 1600, 177);
	App->enemies->AddEnemy(Enemy_Type::DRAGON, 250, 15);
	App->enemies->AddEnemy(Enemy_Type::ORCO, 2000, 150);
	*/
	App->enemies->AddEnemy(Enemy_Type::COLUMN, 300, 130);
	App->enemies->AddEnemy(Enemy_Type::COLUMN, 350, 130);
	App->enemies->AddEnemy(Enemy_Type::COLUMN, 400, 130);

	//App->enemies->AddEnemy(Enemy_Type::BOSS, 180, 65);
	

	

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->Enable();
	App->enemies->Enable();

	return ret;
}

Update_Status SceneLevel1::Update()
{
	App->render->camera.x += 1;
	bgleft->SetPos(App->render->camera.x, 0);
	bgright->SetPos(App->render->camera.x + 310, 0);
	if (App->player->phase == 3 && !App->player->onBeastForm) {
		App->audio->PlayFx(beastHowl);
		App->audio->PlayMusic("Assets/Music/beastForm.ogg", 1.0f);
		App->player->onBeastForm = true;
	}

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
	App->enemies->RemoveColliders();
	
	

	
	return true;
}