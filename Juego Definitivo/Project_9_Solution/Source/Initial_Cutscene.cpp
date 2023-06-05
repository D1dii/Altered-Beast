#include "Initial_Cutscene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"

Initial_Cutscene::Initial_Cutscene(bool startEnabled) : Module(startEnabled)
{

}

Initial_Cutscene::~Initial_Cutscene()
{

}

// Load assets
bool Initial_Cutscene::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	bool onBeastForm = false;

	bgbackTexture = App->textures->Load("Assets/Sprites/backbg.png");
	bgfrontTexture = App->textures->Load("Assets/Sprites/frontbg.png");
	initialScreen = App->textures->Load("Assets/Sprites/initial cutscene.png");





	//Bottomside collider

	bgfront = App->collisions->AddCollider({ 0, 217, 1600, 24 }, Collider::Type::WALL);
	bgright = App->collisions->AddCollider({ 320, 0, 10, 240 }, Collider::Type::SCREEN_RIGHT);
	bgleft = App->collisions->AddCollider({ 0, 0, 10, 240 }, Collider::Type::SCREEN_LEFT);
	App->enemies->AddEnemy(Enemy_Type::INITIAL_SCENE, 30, 40);


	App->player->Disable();
	App->enemies->Enable();

	return ret;
}

Update_Status Initial_Cutscene::Update()
{
	frame++;
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	bgleft->SetPos(App->render->camera.x, 0);
	bgright->SetPos(App->render->camera.x + 310, 0);

	if (frame >= 206)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);

	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status Initial_Cutscene::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgbackTexture, 0, 0, NULL, 0.6f);
	App->render->Blit(bgfrontTexture, 0, 187, NULL, 0.7f);

	return Update_Status::UPDATE_CONTINUE;
}

bool Initial_Cutscene::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();
	App->collisions->RemoveCollider(App->player->collider);
	App->collisions->RemoveCollider(bgleft);
	App->collisions->RemoveCollider(bgright);
	App->collisions->RemoveCollider(bgfront);
	App->enemies->RemoveColliders();




	return true;
};
