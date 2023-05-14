#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"

#include <stdio.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 35 , 12 + 280 * phase, 40, 75 });

	// jump animation
	jumpAnim.PushBack({ 7, 155 + 280 * phase, 40, 68 });

	// Move down
	downAnim.PushBack({ 183, 176, 34, 43 });
	downAnim.loop = false;
	downAnim.speed = 0.1f;

	// Move right
	rightAnim.PushBack({ 75, 12 + 280 * phase, 40, 75 });
	rightAnim.PushBack({ 125, 12 + 280 * phase, 40, 75 });
	rightAnim.PushBack({ 170, 12 + 280 * phase, 40, 75 });
	rightAnim.speed = 0.2f;

	// Move left 
	leftAnim.PushBack({ 75, 12 + 280 * phase, 40, 75 });
	leftAnim.PushBack({ 125, 12 + 280 * phase, 40,75 });
	leftAnim.PushBack({ 170, 12 + 280 * phase, 40, 75 });
	leftAnim.speed = 0.2f;

	// Punch Attack
	punchAnim.PushBack({ 7, 86 + 280 * phase, 52, 72 });
	punchAnim.PushBack({ 66, 87 + 280 * phase, 35, 72 });
	punchAnim.PushBack({ 107, 88 + 280 * phase, 61, 71 });
	punchAnim.speed = 0.2f;
	punchAnim.loop = false;

	// Crouch Punch Attack
	crouchpunchAnim.PushBack({ 223, 181, 57, 37 });
	crouchpunchAnim.speed = 0.1f;
	crouchpunchAnim.loop = false;

	// Kick Attack
	kickAnim.PushBack({ 174, 87 + 280 * phase, 46, 65 });
	kickAnim.PushBack({ 227, 87 + 280 * phase, 36, 65 });
	kickAnim.PushBack({ 269, 86 + 280 * phase, 61, 66 });
	kickAnim.speed = 0.2f;
	kickAnim.loop = false;

	// Crouch Kick Attack
	crouchkickAnim.PushBack({ 287, 188, 52, 30 });
	crouchkickAnim.PushBack({ 346, 165, 49, 53 });
	crouchkickAnim.speed = 0.2f;
	crouchkickAnim.loop = false;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Sprites/protagonist.png");
	currentAnimation = &idleAnim;

	laserFx = App->audio->LoadFx("Assets/Fx/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/Fx/explosion.wav");
	punchFx = App->audio->LoadFx("Assets/Fx/punch.wav");
	jumpFx = App->audio->LoadFx("Assets/Fx/jump.wav");
	playerDeathFx = App->audio->LoadFx("Assets/Fx/screamPlayerDeath.ogg");
	powerUpFx = App->audio->LoadFx("Assets/Fx/power.ogg");

	position.x = 20;
	position.y = 150;

	destroyed = false;

	collider = App->collisions->AddCollider({ position.x + 8, position.y + 8, 25, 50 }, Collider::Type::PLAYER, this);
	punch = App->collisions->AddCollider({ position.x + 20, position.y + 8, 0, 0 }, Collider::Type::PLAYER_ATTACK, this);
	kick = App->collisions->AddCollider({ position.x + 20, position.y + 8, 0, 0 }, Collider::Type::PLAYER_ATTACK, this);
	crouchkick = App->collisions->AddCollider({ position.x + 20, position.y + 8, 0, 0 }, Collider::Type::PLAYER_ATTACK, this);

	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	//char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = App->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);

	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	char lookupTable[] = { "abcdefghijklmnopqrstuvwxyz 1234567890.,'=(?!)+-*/      " };
	scoreFont = App->fonts->Load("Assets/Fonts/typography.png", lookupTable, 2);

	return ret;
}

Update_Status ModulePlayer::Update()
{
	// Moving the player with the camera scroll

	if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT 
		&& playerState != state::JUMP
		&& playerState != state::CROUCH)
	{
		position.x -= speed;
		position.y = 150;
		collider->rect.h = 50;
		playerState = state::MOVEMENT;
		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			flipType = true;
			currentAnimation = &leftAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT 
		&& playerState != state::JUMP
		&& playerState != state::CROUCH)
	{
		position.x += speed;
		position.y = 150;
		collider->rect.h = 50;
		playerState = state::MOVEMENT;
		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			flipType = false;
			currentAnimation = &rightAnim;
		}
	}
	if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_DOWN && playerState != state::JUMP)
	{

		position.y = 175;
		collider->rect.h = 25;
		playerState = state::CROUCH;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}
	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN)
	{
		collider->rect.h = 25;
		playerState = state::JUMP;
		if (currentAnimation != &jumpAnim)
		{
			jumpAnim.Reset();
			currentAnimation = &jumpAnim;
		}
		App->audio->PlayFx(jumpFx);
	}

	if (App->input->keys[SDL_SCANCODE_0] == Key_State::KEY_REPEAT)
	{
		App->audio->PlayFx(powerUpFx);
		phase = 0;
	}
	if (App->input->keys[SDL_SCANCODE_1] == Key_State::KEY_REPEAT)
	{
		App->audio->PlayFx(powerUpFx);
		phase = 1;
	}
	if (App->input->keys[SDL_SCANCODE_2] == Key_State::KEY_REPEAT)
	{
		App->audio->PlayFx(powerUpFx);
		phase = 2;
	}

	switch (playerState) {
	case state::IDLE:
		punch->rect.w = 0;
		punch->rect.h = 0;
		punch->rect.y = 0;
		kick->rect.w = 0;
		kick->rect.h = 0;
		kick->rect.y = 0;
		crouchkick->rect.w = 0;
		crouchkick->rect.h = 0;
		crouchkick->rect.y = 10;
		if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN) {
			punchAnim.Reset();
			playerState = state::PUNCH;
			App->audio->PlayFx(punchFx);
			
		}
		else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN)
		{
			kickAnim.Reset();
			playerState = state::KICK;
			App->audio->PlayFx(punchFx);
		}
		break;

	case state::MOVEMENT:
		if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN)
		{
			punchAnim.Reset();
			playerState = state::PUNCH;
		}
		break;

	case state::CROUCH:
		currentAnimation = &downAnim;
		downAnim.Update();
		position.y = 175;
		punch->rect.w = 0;
		punch->rect.h = 0;
		punch->rect.y = 0;
		kick->rect.w = 0;
		kick->rect.h = 0;
		kick->rect.y = 0;
		crouchkick->rect.w = 0;
		crouchkick->rect.h = 0;
		crouchkick->rect.y = 0;
		if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN)
		{
			crouchpunchAnim.Reset();
			playerState = state::CROUCH_PUNCH;
			App->audio->PlayFx(punchFx);
		}
		else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN)
		{
			crouchkickAnim.Reset();
			playerState = state::CROUCH_KICK;
			App->audio->PlayFx(punchFx);
		}
		break;
	case state::JUMP:
		currentAnimation = &jumpAnim;
		jumpAnim.Update();
		frame++;
		if (frame <= 32) {
			position.y -= speedY;
			speedY += gravity;
		}
		else {
			frame = 0;
			speedY = 16;
			playerState = state::IDLE;
		}
			
		
		break;
	case state::PUNCH:
		currentAnimation = &punchAnim;
		punchAnim.Update();
		frame++;
		position.y = 153;
		punch->rect.w = 42;
		punch->rect.h = 10;
		if (frame >= 20)
		{
			playerState = state::IDLE;
			frame = 0;
		}
		
		break;
	case state::KICK:
		currentAnimation = &kickAnim;
		kickAnim.Update();
		frame++;
		position.y = 152;
		kick->rect.w = 45;
		kick->rect.h = 20;
		kick->rect.x = position.x + 20;
		kick->rect.y = position.y + 35;
		if (frame >= 30)
		{
			playerState = state::IDLE;
			frame = 0;
		}
		break;
	case state::CROUCH_PUNCH:
		currentAnimation = &crouchpunchAnim;
		crouchpunchAnim.Update();
		frame++;
		position.y = 180;
		punch->rect.w = 40;
		punch->rect.h = 10;
		if (frame >= 10) {
			playerState = state::CROUCH;
			frame = 0;
		}
		break;
	case state::CROUCH_KICK:
		currentAnimation = &crouchkickAnim;
		crouchkickAnim.Update();
		frame++;
		position.y = 165;
		crouchkick->rect.x = position.x + 25;
		crouchkick->rect.y = position.y - 2;
		crouchkick->rect.w = 18;
		crouchkick->rect.h = 40;
		if (frame >= 30)
		{
			playerState = state::CROUCH;
			frame = 0;
		}
	}

	
	//This is for loading the new animations 
	if (phase == 1 || phase == 0) {
		idleAnim.PullBack(1);
		idleAnim.PushBack({ 35 , 12 + 280 * phase, 40, 73 });
		rightAnim.PullBack(3);
		rightAnim.PushBack({ 75, 12 + 280 * phase, 40, 73 });
		rightAnim.PushBack({ 125, 12 + 280 * phase, 40, 73 });
		rightAnim.PushBack({ 170, 12 + 280 * phase, 40, 73 });
		leftAnim.PullBack(3);
		leftAnim.PushBack({ 75, 12 + 280 * phase, 40, 73 });
		leftAnim.PushBack({ 125, 12 + 280 * phase, 40,73 });
		leftAnim.PushBack({ 170, 12 + 280 * phase, 40, 73 });
		punchAnim.PullBack(3);
		punchAnim.PushBack({ 7, 86 + 280 * phase, 52, 71 });
		punchAnim.PushBack({ 66, 87 + 280 * phase, 35, 71 });
		punchAnim.PushBack({ 107, 88 + 280 * phase, 61, 71 }); 
		downAnim.PullBack(1);
		downAnim.PushBack({ 183, 176 + 280 * phase , 35, 43 });

		kickAnim.PullBack(3);
		kickAnim.PushBack({ 174, 87 + 280 * phase, 46, 65 });
		kickAnim.PushBack({ 227, 87 + 280 * phase, 36, 65 });
		kickAnim.PushBack({ 269, 86 + 280 * phase, 61, 66 });


		jumpAnim.PullBack(1);
		jumpAnim.PushBack({ 7, 155 + 280 * phase, 40, 68 });
	}
	if (phase == 2) {

		idleAnim.PullBack(1);
		idleAnim.PushBack({ 40 , 579, 45 , 75 });
		rightAnim.PullBack(3);
		rightAnim.PushBack({ 85, 579, 44, 75 });
		rightAnim.PushBack({ 135, 579, 44, 75 });
		rightAnim.PushBack({ 180, 579, 44, 75 });
		leftAnim.PullBack(3);
		leftAnim.PushBack({ 85, 579, 44, 75 });
		leftAnim.PushBack({ 135, 579, 44,75 });
		leftAnim.PushBack({ 180, 579, 44, 75 });

		punchAnim.PullBack(2);
		punchAnim.PushBack({ 0, 657, 44, 75 });
		punchAnim.PushBack({ 67, 657, 60, 75 });
		
		kickAnim.PullBack(3);
		kickAnim.PushBack({ 167, 657, 44, 75 });
		kickAnim.PushBack({ 228, 657, 44, 75 });
		kickAnim.PushBack({ 272,657, 75, 75 });

		downAnim.PullBack(1);
		downAnim.PushBack({ 254, 747, 50, 43 });

		jumpAnim.PullBack(1);
		jumpAnim.PushBack({ 5, 735, 45, 55 });
	}



	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_IDLE
		&& playerState != state::PUNCH
		&& playerState != state::KICK
		&& playerState != state::JUMP)
	{
		currentAnimation = &idleAnim;
		position.y = 150;
		collider->rect.h = 50;
		playerState = state::IDLE;
	}
	//If Punch state / crounch / punch crounch / crounch kick

	collider->SetPos(position.x + 8, position.y + 8);
	if (flipType) {
		punch->SetPos(position.x - 2, position.y + 8);
		crouchkick->SetPos(position.x + 3, position.y - 2);
		kick->SetPos(position.x - 5, position.y + 35);
	}
	else {
		punch->SetPos(position.x + 20, position.y + 8);
		crouchkick->SetPos(position.x + 25, position.y - 2);
		kick->SetPos(position.x + 20, position.y + 35);
	}

	currentAnimation->Update();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect, speed, flipType);
	}

	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%7d", score);

	// TODO 3: Blit the text of the score in at the bottom of the screen
	App->fonts->BlitText(0, 20, scoreFont, scoreText);
	App->fonts->BlitText(100, 20, scoreFont, scoreText);
    secondscounter++;
if (secondscounter %100 ==0){

	secondscounter=0;
}
else if (secondscounter >50){
	App->fonts->BlitText(200, 20, scoreFont, "insert coin");
}

	if (score >= 400) {
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);
		
	}

	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && destroyed == false && c2->type == collider->WALL)
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);

		App->audio->PlayFx(explosionFx);
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);

		destroyed = true;
	}
	else if (c2->type == collider->SCREEN_LEFT)
	{
		position.x += 2;
	}
	else if (c2->type == collider->SCREEN_RIGHT)
	{
		position.x -= 2;
	}

	if (c1->type == Collider::Type::PLAYER_ATTACK && c2->type == Collider::Type::ENEMY)
	{
		//score += 23;
	}

	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ENEMY_SHOT && destroyed == false) {
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);
		
		destroyed = true;
	}

	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ITEM) {
		App->audio->PlayFx(powerUpFx);
		if (phase < 3) {
			phase++;
		}

		
	}
}