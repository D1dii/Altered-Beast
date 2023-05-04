#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"

SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled)
{

}

SceneIntro::~SceneIntro()
{

}

// Load assets
bool SceneIntro::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	Intro2 = App->textures->Load("Assets/Sprites/Intro 2.png");
	Intro1v1 = App->textures->Load("Assets/Sprites/Intro 1 v1.png");
	Intro1v2 = App->textures->Load("Assets/Sprites/Intro 1 v2.png");
	Sega = App->textures->Load("Assets/Sprites/Sega.png");
	//App->audio->PlayMusic("Assets/Music/introTitle.ogg", 1.0f);
	coin = App->audio->LoadFx("Assets/Fx/coin.wav");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneIntro::Update()
{
	frame++;

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
		App->audio->PlayFx(coin);
		App->player->score = 0;
		App->player->phase = 0;
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(Intro2, 0, 40, NULL);
	App->render->Blit(Sega, 320, 200, NULL);

	if (frame <= 210) {
		App->render->Blit(Sega, 320 - frame, 170, NULL);
		
	}

	else  {

		App->render->Blit(Intro1v1, -25, 23, NULL);

		if (frame<220){

          App->render->Blit(Intro1v2, -25, 23, NULL);

		}
		if(frame>225){

			App->render->Blit(Intro1v1, -25, 23, NULL);
		}

		App->render->Blit(Sega, 320 - 210, 170, NULL);
	}

	return Update_Status::UPDATE_CONTINUE;
}