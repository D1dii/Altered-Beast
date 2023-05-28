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
#include "ModuleEnemies.h"

#include <stdio.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 35 , 12 + 280 * phase, 40, 75 });

	// jump animation
	jumpAnim.PushBack({ 7, 155 + 280 * phase, 40, 68 });

	//Nodes anim
	nodesAnim[0].PushBack({ 0, 0, 23, 14 });
	nodesAnim[1].PushBack({ 0, 14, 23, 14 });
	nodesAnim[2].PushBack({ 0, 14 * 2, 23, 14 });
	nodesAnim[3].PushBack({ 0, 14 * 3, 23, 14 });

	//lifes anim
	lifesAnim[0].PushBack({ 14, 22, 63, 33 });
	lifesAnim[1].PushBack({ 14, 106, 63, 33 });
	lifesAnim[2].PushBack({ 14, 186, 63, 33 });

	// Move down
	downAnim.PushBack({ 183, 176, 34, 43 });
	downAnim.loop = false;
	downAnim.speed = 0.1f;

	// Move right
	rightAnim.PushBack({ 75, 12 + 280 * phase, 40, 75 });
	rightAnim.PushBack({ 125, 12 + 280 * phase, 40, 75 });
	rightAnim.PushBack({ 170, 12 + 280 * phase, 40, 75 });
	rightAnim.speed = 0.1f;

	// Move left 
	leftAnim.PushBack({ 75, 12 + 280 * phase, 40, 75 });
	leftAnim.PushBack({ 125, 12 + 280 * phase, 40,75 });
	leftAnim.PushBack({ 170, 12 + 280 * phase, 40, 75 });
	leftAnim.speed = 0.1f;

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
	numLifes = 2;
	lifeNodes = 12;

	texture = App->textures->Load("Assets/Sprites/protagonist.png");
	nodesTexture = App->textures->Load("Assets/Sprites/lifeSprite2.png");
	uiTexture = App->textures->Load("Assets/Sprites/lifes.png");
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

	collider = App->collisions->AddCollider({ position.x + 8, position.y + 8, 25, 70 }, Collider::Type::PLAYER, this);
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

	GamePad& pad = App->input->pads[0];

	//Debug key for gamepad rumble testing purposes
	if (App->input->keys[SDL_SCANCODE_1] == Key_State::KEY_DOWN)
	{
		App->input->ShakeController(0, 12, 0.33f);
	}

	//Debug key for gamepad rumble testing purposes
	if (App->input->keys[SDL_SCANCODE_2] == Key_State::KEY_DOWN)
	{
		App->input->ShakeController(0, 36, 0.66f);
	}

	//Debug key for gamepad rumble testing purposes
	if (App->input->keys[SDL_SCANCODE_3] == Key_State::KEY_DOWN)
	{
		App->input->ShakeController(0, 60, 1.0f);
	}

	if (App->input->keys[SDL_SCANCODE_0] == Key_State::KEY_REPEAT)
	{
		App->audio->PlayFx(powerUpFx);
		phase = 0;
		phaseUpdate();
	}
	if (App->input->keys[SDL_SCANCODE_1] == Key_State::KEY_REPEAT)
	{
		App->audio->PlayFx(powerUpFx);
		phase = 1;
		phaseUpdate();
	}
	if (App->input->keys[SDL_SCANCODE_2] == Key_State::KEY_REPEAT)
	{
		App->audio->PlayFx(powerUpFx);
		phase = 2;
		phaseUpdate();
	}

	// Spawn Enemies
	if (App->input->keys[SDL_SCANCODE_F6] == Key_State::KEY_DOWN) {
		App->enemies->AddEnemy(Enemy_Type::ZOMBIE, position.x + 200, 158);
	}

	if (App->input->keys[SDL_SCANCODE_F7] == Key_State::KEY_DOWN) {
		App->enemies->AddEnemy(Enemy_Type::NO_SKULL, position.x + 200, 156);
	}

	if (App->input->keys[SDL_SCANCODE_F8] == Key_State::KEY_DOWN) {
		App->enemies->AddEnemy(Enemy_Type::WOLF, position.x + 200, 177);
	}

	if (App->input->keys[SDL_SCANCODE_F9] == Key_State::KEY_DOWN) {
		App->enemies->AddEnemy(Enemy_Type::WOLF_BLUE, position.x + 200, 177);
	}

	if (App->input->keys[SDL_SCANCODE_F10] == Key_State::KEY_DOWN) {
		App->enemies->AddEnemy(Enemy_Type::DRAGON, position.x + 200, 15);
	}

	if (App->input->keys[SDL_SCANCODE_F11] == Key_State::KEY_DOWN) {
		App->enemies->AddEnemy(Enemy_Type::ORCO, position.x + 200, 150);
	}

	switch (playerState) {
	case state::IDLE:
		
		if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN || pad.x == 1) {
			punchAnim.Reset();
			playerState = state::PUNCH;
			App->audio->PlayFx(punchFx);
			
		}
		else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN || pad.b == 1)
		{
			kickAnim.Reset();
			playerState = state::KICK;
			App->audio->PlayFx(punchFx);
		} 
		else if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT 
			|| pad.l_x < 0 
			|| App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT 
			|| pad.l_x > 0)
		{
			playerState = state::MOVEMENT;
		} else if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_DOWN
			|| (pad.l_x > -0.2f && pad.l_x < 0.2f && pad.l_y > 0)) {
			playerState = state::CROUCH;
		}
		else if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN || pad.a == 1) {
			playerState = state::JUMP;
		}
		break;
	case state::MOVEMENT:
		if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT || pad.l_x < 0) {
			position.x -= speed;
			isInAColumn(62, 150, false);
			collider->rect.h = 70;
			if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN || pad.a == 1)
			{
				jumpAnim.Reset();
				playerState = state::JUMP;
			}
			else if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN || pad.x == 1)
			{
				punchAnim.Reset();
				playerState = state::PUNCH;
				App->audio->PlayFx(punchFx);
			}
			else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN || pad.b == 1)
			{
				kickAnim.Reset();
				playerState = state::KICK;
				App->audio->PlayFx(punchFx);
			}
			else if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_DOWN
				|| (pad.l_x > -0.2f && pad.l_x < 0.2f && pad.l_y > 0))
			{
				downAnim.Reset();
				playerState = state::CROUCH;
			}
			else if (currentAnimation != &leftAnim)
			{
				leftAnim.Reset();
				flipType = true;
				currentAnimation = &leftAnim;
			}
			leftAnim.Update();
		}
		else if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT || pad.l_x > 0) {
			position.x += speed * 2;
			isInAColumn(62, 153, false);
			collider->rect.h = 70;
			if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN || pad.a == 1)
			{
				jumpAnim.Reset();
				playerState = state::JUMP;
			}
			else if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN || pad.x == 1)
			{
				punchAnim.Reset();
				playerState = state::PUNCH;
				App->audio->PlayFx(punchFx);
			}
			else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN || pad.b == 1)
			{
				kickAnim.Reset();
				playerState = state::KICK;
				App->audio->PlayFx(punchFx);
			}
			else if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_DOWN
				|| (pad.l_x > -0.2f && pad.l_x < 0.2f && pad.l_y > 0))
			{
				downAnim.Reset();
				currentAnimation = &downAnim;
				playerState = state::CROUCH;
			}
			else if (currentAnimation != &rightAnim)
			{
				rightAnim.Reset();
				flipType = false;
				currentAnimation = &rightAnim;
			}
			
			rightAnim.Update();
		}
		else if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_IDLE
			|| App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_IDLE) {
			playerState = state::IDLE;
		}
		break;
	case state::CROUCH:
		isInAColumn(90, 175, true);
		collider->rect.h = 45;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
		downAnim.Update();
		punch->rect.w = 0;
		punch->rect.h = 0;
		punch->SetPos(position.x + 20, 0);
		kick->rect.w = 0;
		kick->rect.h = 0;
		kick->SetPos(position.x + 20, 0);
		crouchkick->rect.w = 0;
		crouchkick->rect.h = 0;
		crouchkick->SetPos(position.x + 20, 0);
		if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN || pad.x == 1)
		{
			crouchpunchAnim.Reset();
			playerState = state::CROUCH_PUNCH;
			App->audio->PlayFx(punchFx);
		}
		else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN || pad.b == 1)
		{
			crouchkickAnim.Reset();
			playerState = state::CROUCH_KICK;
			App->audio->PlayFx(punchFx);
		}
		else if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN || pad.a == 1) 
		{
			playerState = state::JUMP;
		}
		else if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT
			|| pad.l_x < 0
			|| App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT
			|| pad.l_x > 0)
		{
			playerState = state::MOVEMENT;
		}

		break;
	case state::JUMP:
		collider->rect.h = 25;
		if (currentAnimation != &jumpAnim)
		{
			App->audio->PlayFx(jumpFx);
			jumpAnim.Reset();
			currentAnimation = &jumpAnim;
		}
		jumpAnim.Update();
		frame++;
		if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN || pad.x == 1)
		{
			currentAnimation = &punchAnim;
			punchAnim.Update();
			punch->rect.w = 42;
			punch->rect.h = 10;
			if (flipType) {
				punch->SetPos(position.x - 2, position.y + 8);
			}
			else {
				punch->SetPos(position.x + 20, position.y + 8);
			}
			if (frame >= 20)
			{
				playerState = state::JUMP;
			}
		}
		else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN || pad.b == 1)
		{
			kickAnim.Reset();
			playerState = state::KICK;
			App->audio->PlayFx(punchFx);
		}
		if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT || pad.l_x < 0)
		{
			position.x -= 2;
		}
		if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT || pad.l_x > 0)
		{
			position.x += 2;
		}
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
		punch->rect.w = 42;
		punch->rect.h = 10;
		if (flipType) {
			punch->SetPos(position.x - 2, position.y + 8);
		}
		else {
			punch->SetPos(position.x + 20, position.y + 8);
		}
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
		kick->rect.w = 45;
		kick->rect.h = 20;
		if (flipType) {
			kick->SetPos(position.x - 5, position.y + 35);
		}
		else {
			kick->SetPos(position.x + 20, position.y + 35);
		}
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
		isInAColumn(90, 180, true);

		punch->rect.w = 40;
		punch->rect.h = 10;
		if (flipType) {
			punch->SetPos(position.x - 2, position.y + 8);
		}
		else {
			punch->SetPos(position.x + 20, position.y + 8);
		}
		if (frame >= 10) {
			playerState = state::CROUCH;
			frame = 0;
		}
		break;
	case state::CROUCH_KICK:
		currentAnimation = &crouchkickAnim;
		crouchkickAnim.Update();
		frame++;
		isInAColumn(80, 165, true);
		crouchkick->rect.w = 18;
		crouchkick->rect.h = 40;
		if (flipType)
		{
			crouchkick->SetPos(position.x + 3, position.y - 2);
		}
		else
		{
			crouchkick->SetPos(position.x + 25, position.y - 2);
		}
		if (frame >= 30)
		{
			playerState = state::CROUCH;
			frame = 0;
		}
	}
	if (App->input->keys[SDL_SCANCODE_F2] == Key_State::KEY_DOWN) {
		GODMODE = !GODMODE;
	}
	
	//This is for loading the new animations 
	
	if (App->input->keys[SDL_SCANCODE_M] == Key_State::KEY_DOWN) {
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 90);

	}
	if (App->input->keys[SDL_SCANCODE_B] == Key_State::KEY_DOWN) {
		App->audio->PlayFx(playerDeathFx);
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 90);
		

	}
	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_IDLE
		&& playerState != state::PUNCH
		&& playerState != state::KICK
		&& playerState != state::JUMP
		&& pad.l_x == 0
		&& pad.l_y == 0)
	{
		currentAnimation = &idleAnim;
		isInAColumn(62, 150, false);
		collider->rect.h = 70;
		playerState = state::IDLE;
		punch->rect.w = 0;
		punch->rect.h = 0;
		punch->SetPos(position.x + 20, 0);
		kick->rect.w = 0;
		kick->rect.h = 0;
		kick->SetPos(position.x + 20, 0);
		crouchkick->rect.w = 0;
		crouchkick->rect.h = 0;
		crouchkick->SetPos(position.x + 20, 0);
	}
	//If Punch state / crounch / punch crounch / crounch kick

	collider->SetPos(position.x + 8, position.y + 8);

	currentAnimation->Update();
	if (GODMODE == true) {
		App->player->collider->NONE;
	}
	else {
		waitForDmg++;
		if (waitForDmg >= 30) {
			damaged = false;
			PlayerTouch = true;
			waitForDmg = 0;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
	
	
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect, speed, flipType);
	}
	//Draw Nodes
	int blueNodes = lifeNodes >> 2;
	for (int i = 0; i < blueNodes; i++)
	{
		SDL_Rect rect = nodesAnim[0].GetCurrentFrame();
		App->render->Blit(nodesTexture, 50+ 25 * i, 230, &rect, NULL, NULL, true);
	}
	if (lifeNodes % 4 == 3)
	{
		SDL_Rect rect = nodesAnim[1].GetCurrentFrame();
		App->render->Blit(nodesTexture, 50 + 25 * (blueNodes), 230, &rect, NULL, NULL, true);
	}
	else if (lifeNodes % 4 == 2)
	{
		SDL_Rect rect = nodesAnim[2].GetCurrentFrame();
		App->render->Blit(nodesTexture, 50 + 25 * (blueNodes), 230, &rect, NULL, NULL, true);
	}
	else if (lifeNodes % 4 == 1)
	{
		SDL_Rect rect = nodesAnim[3].GetCurrentFrame();
		App->render->Blit(nodesTexture, 50 + 25 * (blueNodes), 230, &rect, NULL, NULL, true);
	}

	//Draw Lifes
	if (numLifes == 2)
	{
		SDL_Rect rect = lifesAnim[0].GetCurrentFrame();
		App->render->Blit(uiTexture, 10,50, &rect, NULL, NULL, true);
	}
	else if (numLifes == 1)
	{
		SDL_Rect rect = lifesAnim[1].GetCurrentFrame();
		App->render->Blit(uiTexture, 10, 50, &rect, NULL, NULL, true);
	}
	else if (numLifes == 0)
	{
		SDL_Rect rect = lifesAnim[2].GetCurrentFrame();
		App->render->Blit(uiTexture, 10, 50, &rect, NULL, NULL, true);
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

	if (score >= 4000) {
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);
		
	}

	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::phaseUpdate() {
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

	if (phase == 0) {
		damage = 1;
	}
	else if (phase == 1) {
		damage = 2;
	}
	else if (phase == 2) {
		damage = 3;
	}
	else if (phase == 4) {
		damage = 4;
	}
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
		position.x += 4;
	}
	else if (c2->type == collider->SCREEN_RIGHT)
	{
		position.x -= 4;
	}

	if (c1->type == Collider::Type::PLAYER_ATTACK && c2->type == Collider::Type::ENEMY)
	{
		//score += 23;
	}
	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::COLUMNS)
	{
		if (position.y < 150)
		{
			inAColumn = true;
		}
		else if (position.x < c2->rect.x)
		{
			position.x -= 2;
		}
		else if (position.x > c2->rect.x)
		{
			position.x += 2;
		}

	}

	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ENEMY_SHOT && destroyed == false && PlayerTouch == true)
	{
		//c2->pendingToDelete = true;
		lifeNodes--;
		damaged = true;
		PlayerTouch = false;
		if (lifeNodes <= 0)
		{
			lifeNodes = 12;
			numLifes--;
			if (numLifes < 0)
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);
				destroyed = true;
			}
		}

	}

	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ITEM) {
		App->audio->PlayFx(powerUpFx);
		if (phase < 3) {
			phase++;
		}
		phaseUpdate();
		
	}
}