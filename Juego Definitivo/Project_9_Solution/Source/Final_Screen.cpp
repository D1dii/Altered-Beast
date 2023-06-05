#include "Final_Screen.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

FinalScreen::FinalScreen(bool startEnabled) : Module(startEnabled)
{

}

FinalScreen::~FinalScreen()
{

}

bool FinalScreen::Start() {

	LOG("Loading background assets");

	bool ret = true;

	final = App->textures->Load("Assets/Sprites/Final_Screen.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status FinalScreen::Update() {


	return Update_Status::UPDATE_CONTINUE;
}

Update_Status FinalScreen::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(final, 90, 55, NULL);


	return Update_Status::UPDATE_CONTINUE;
}