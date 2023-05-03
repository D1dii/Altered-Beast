#include "InitialScreen.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

Initial_Screen::Initial_Screen(bool startEnabled) : Module(startEnabled)
{

}

Initial_Screen::~Initial_Screen()
{

}

// Load assets
bool Initial_Screen::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	intro = App->textures->Load("Assets/Sprites/InitialScreen1.png");

	
	

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status Initial_Screen::Update()
{
	frame++;

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
		
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status Initial_Screen::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(intro, 0, 40, NULL);
	

	return Update_Status::UPDATE_CONTINUE;
}