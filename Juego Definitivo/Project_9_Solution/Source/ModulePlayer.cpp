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
#include "SceneLevel1.h"

#include <stdio.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{

	////Nodes anim
	nodesAnim[0].PushBack({ 0, 0, 23, 14 });
	nodesAnim[1].PushBack({ 0, 14, 23, 14 });
	nodesAnim[2].PushBack({ 0, 14 * 2, 23, 14 });
	nodesAnim[3].PushBack({ 0, 14 * 3, 23, 14 });

	////lifes anim
	lifesAnim[0].PushBack({ 14, 22, 63, 33 });
	lifesAnim[1].PushBack({ 14, 106, 63, 33 });
	lifesAnim[2].PushBack({ 14, 186, 63, 33 });



	//// FASE 0 idle animation 
	idleAnim[0].PushBack({ 96 + 25 , 0, 96 - 50, 73 });

	//// FASE 0 jump animation
	jumpAnim[0].PushBack({ 1 + 25, 146, 96 - 50, 73 });



	// FASE 0 Move crouch 
	downAnim[0].PushBack({ 288 + 25, 146 + 25, 96 - 50, 73 - 25 });
	downAnim[0].speed = 0.1f;
	downAnim[0].loop = false;

	// FASE 0 Move right
	//
	rightAnim[0].PushBack({ 192 + 25, 1, 96 - 50, 73 });
	rightAnim[0].PushBack({ 192 + 96 + 25, 1, 96 - 50, 73 });
	rightAnim[0].PushBack({ 192 + 96 + 96 + 25, 1, 96 - 50, 73 });
	rightAnim[0].speed = 0.1f;


	//// FASE 0 Move left 
	leftAnim[0].PushBack({ 192 + 25, 1, 96 - 50, 73 });
	leftAnim[0].PushBack({ 192 + 96 + 25 , 1, 96 - 50, 73 });
	leftAnim[0].PushBack({ 192 + 96 + 96 + 25, 1, 96 - 50, 73 });
	leftAnim[0].speed = 0.1f;

	//// FASE 0 Punch Attack
	punchAnim[0].PushBack({ 1 + 25, 73, 96 - 25 - 15, 73 });
	punchAnim[0].PushBack({ 1 + 96 + 25, 73, 96 - 25 - 15, 73 });
	punchAnim[0].PushBack({ 1 + 96 + 96 + 25,73, 96 - 25 - 15, 73 });
	punchAnim[0].speed = 0.2f;
	punchAnim[0].loop = false;


	//// FASE 0 Crouch Punch Attack
	crouchpunchAnim[0].PushBack({ 384 + 25,146 + 30, 96 - 25 - 15, 73 - 30 });
	crouchpunchAnim[0].speed = 0.1f;
	crouchpunchAnim[0].loop = false;


	//// FASE 0 Kick Attack
	kickAnim[0].PushBack({ 288 + 96 + 10,73, 96 - 30, 73 });
	kickAnim[0].PushBack({ 288 + 96 + 10, 73, 96 - 30, 73 });
	kickAnim[0].PushBack({ 288 + 96 + 96 + 10, 73, 96 - 30, 73 });
	kickAnim[0].speed = 0.2f;
	kickAnim[0].loop = false;

	//// FASE 0 Crouch Kick Attack 
	crouchkickAnim[0].PushBack({ 480 + 20, 146 + 15, 96 - 40, 73 });
	crouchkickAnim[0].PushBack({ 480 + 96 + 20, 146 + 15, 96 - 40, 73 });
	crouchkickAnim[0].speed = 0.2f;
	crouchkickAnim[0].loop = false;

	//FASE 0 stun
	stunAnim[0].PushBack({ 1 + 25, 220,  96 - 50, 73 });
	stunAnim[0].PushBack({ 96 + 25, 220, 96 - 50, 73 });
	stunAnim[0].speed = 0.05f;
	stunAnim[0].loop = false;

	//FASE 0 death
	deathAnim[0].PushBack({ 1 + 25, 220,  96 - 50, 73 });
	deathAnim[0].PushBack({ 200,  220, 80, 73 });
	deathAnim[0].PushBack({ 290,  220, 85, 73 });
	deathAnim[0].speed = 0.02f;
	deathAnim[0].loop = false;





	//// FASE 1 idle animation 
	idleAnim[1].PushBack({ 96 + 25 , 292, 96 - 50, 73 });

	//// FASE 1 jump animation
	jumpAnim[1].PushBack({ 1 + 25, 439, 96 - 50, 73 });

	//// FASE 1 Move crouch 
	downAnim[1].PushBack({ 288 + 25,438 + 25, 96 - 50, 73 - 25 });
	downAnim[1].speed = 0.1f;
	downAnim[1].loop = false;

	//// FASE 1 Move right

	rightAnim[1].PushBack({ 192 + 25, 292, 96 - 50, 73 });
	rightAnim[1].PushBack({ 192 + 96 + 25, 292, 96 - 50, 73 });
	rightAnim[1].PushBack({ 192 + 96 + 96 + 25, 292 , 96 - 50, 73 });
	rightAnim[1].speed = 0.1f;


	//// FASE 1 Move left 
	leftAnim[1].PushBack({ 192 + 25, 292, 96 - 50, 73 });
	leftAnim[1].PushBack({ 192 + 96 + 25 ,292, 96 - 50, 73 });
	leftAnim[1].PushBack({ 192 + 96 + 96 + 25,292, 96 - 50, 73 });
	leftAnim[1].speed = 0.1f;


	//// FASE 1 Punch Attack
	punchAnim[1].PushBack({ 1 + 25,365, 96 - 25 - 17, 73 });
	punchAnim[1].PushBack({ 1 + 96 + 25, 365, 96 - 25 - 17, 73 });
	punchAnim[1].PushBack({ 1 + 96 + 96 + 25,365, 96 - 25 - 17, 73 });
	punchAnim[1].speed = 0.2f;
	punchAnim[1].loop = false;


	//// FASE 1 Crouch Punch Attack
	crouchpunchAnim[1].PushBack({ 384 + 25,438 + 30, 96 - 25 - 10, 73 - 30 });
	crouchpunchAnim[1].speed = 0.1f;
	crouchpunchAnim[1].loop = false;
	//

	//// FASE 1 Kick Attack
	kickAnim[1].PushBack({ 288 + 10,365 , 96 - 20, 73 });
	kickAnim[1].PushBack({ 288 + 96 + 10, 365 , 96 - 20, 73 });
	kickAnim[1].PushBack({ 288 + 96 + 96 + 10, 365, 96 - 20, 73 });
	kickAnim[1].speed = 0.2f;
	kickAnim[1].loop = false;

	//// FASE 1 Crouch Kick Attack 
	crouchkickAnim[1].PushBack({ 480 + 20, 438 + 15, 96 - 40, 73 });
	crouchkickAnim[1].PushBack({ 480 + 96 + 20, 438 + 15, 96 - 40, 73 });
	crouchkickAnim[1].speed = 0.2f;
	crouchkickAnim[1].loop = false;



	//FASE 1 stun
	stunAnim[1].PushBack({ 1 + 25, 220 + 292,  96 - 50, 73 });
	stunAnim[1].PushBack({ 96 + 25, 220 + 292, 96 - 50, 73 });
	stunAnim[1].speed = 0.05f;
	stunAnim[1].loop = false;

	//FASE 1 death
	deathAnim[1].PushBack({ 1 + 25, 220 + 292,  96 - 50, 73 });
	deathAnim[1].PushBack({ 290,  220 + 292, 80, 73 });
	deathAnim[1].PushBack({ 365 + 25,  220 + 292, 85, 73 });
	deathAnim[1].speed = 0.02f;
	deathAnim[1].loop = false;



	// FASE 2 idle animation 
	idleAnim[2].PushBack({ 96 + 25 , 584, 96 - 50, 73 });

	// FASE 2 jump animation
	jumpAnim[2].PushBack({ 1 + 25, 730  , 96 - 50, 73 });
	// FASE 2 Move crouch 
	downAnim[2].PushBack({ 288,755, 52, 50 });
	downAnim[2].speed = 0.1f;
	downAnim[2].loop = false;

	// FASE 2 Move right

	rightAnim[2].PushBack({ 192 + 25, 584, 96 - 50, 73 });
	rightAnim[2].PushBack({ 192 + 96 + 25, 584, 96 - 50, 73 });
	rightAnim[2].PushBack({ 192 + 96 + 96 + 25,  584, 96 - 50, 73 });
	rightAnim[2].speed = 0.1f;

	// FASE 2 Move left 
	leftAnim[2].PushBack({ 192 + 25, 584, 96 - 50, 73 });
	leftAnim[2].PushBack({ 192 + 96 + 25 ,584, 96 - 50, 73 });
	leftAnim[2].PushBack({ 192 + 96 + 96 + 25,584, 96 - 50, 73 });
	leftAnim[2].speed = 0.1f;


	// FASE 2 Punch Attack
	punchAnim[2].PushBack({ 0 + 25,657, 96 - 25 - 15, 73 });
	punchAnim[2].PushBack({ 0 + 96 + 25, 657, 96 - 25 - 15, 73 });
	punchAnim[2].PushBack({ 0 + 96 + 25, 657, 96 - 25 - 15, 73 });
	punchAnim[2].speed = 0.2f;
	punchAnim[2].loop = false;


	// FASE 2 Crouch Punch Attack
	crouchpunchAnim[2].PushBack({ 384 , 730 + 30 , 96 - 20, 73 - 30 });
	crouchpunchAnim[2].PushBack({ 384 + 96 , 730 + 30 , 96 - 20,73 - 30 });
	crouchpunchAnim[2].speed = 0.2f;
	crouchpunchAnim[2].loop = false;


	// FASE 2 Kick Attack
	kickAnim[2].PushBack({ 288 + 10 - 96,657, 96 - 20, 73 });
	kickAnim[2].PushBack({ 288 + 10, 657, 96 - 20, 73 });
	kickAnim[2].PushBack({ 288 + 96 + 10, 657, 96 - 20, 73 });
	kickAnim[2].speed = 0.2f;
	kickAnim[2].loop = false;

	// FASE 2 Crouch Kick Attack 
	crouchkickAnim[2].PushBack({ 576,730 + 15, 96 - 40, 73 });
	crouchkickAnim[2].PushBack({ 576 + 96 , 730 + 15, 96 - 40, 73 });
	crouchkickAnim[2].speed = 0.2f;
	crouchkickAnim[2].loop = false;
	//FASE 2 stun
	stunAnim[2].PushBack({ 1 + 25, 220 + 292,  96 - 50, 73 });
	stunAnim[2].PushBack({ 96 + 25, 220 + 292, 96 - 50, 73 });
	stunAnim[2].speed = 0.05f;
	stunAnim[2].loop = false;

	//FASE 2 death
	deathAnim[2].PushBack({ 1 + 25, 805,  96 - 50, 73 });
	deathAnim[2].PushBack({ 200,  805, 80, 73 });
	deathAnim[2].PushBack({ 290, 805, 85, 73 });
	deathAnim[2].speed = 0.02f;
	deathAnim[2].loop = false;


	// FASE 3 idle animation 
	idleAnim[3].PushBack({ 1 + 25 , 876, 96 - 50, 73 });

	// FASE 3 jump animation
	jumpAnim[3].PushBack({ 96 * 3 + 25,   960, 96 - 50 , 1022 - 960 });

	// FASE 3 Move crouch 
	downAnim[3].PushBack({ 7, 985,83, 40 });
	downAnim[3].speed = 0.1f;
	downAnim[3].loop = false;

	// FASE 3 Move right
	rightAnim[3].PushBack({ 96 + 25,  876, 96 - 50, 73 });
	rightAnim[3].PushBack({ 96 * 2 + 25,  876, 96 - 50 , 73 });
	rightAnim[3].PushBack({ 96 * 3 + 25,   876, 96 - 50 , 73 });
	rightAnim[3].PushBack({ 96 * 4 + 25,  876, 96 - 50 , 73 });
	rightAnim[3].PushBack({ 96 * 5 + 25,   876, 96 - 50 , 73 });
	rightAnim[3].speed = 0.1f;

	// FASE 3 Move left 
	leftAnim[3].PushBack({ 96 + 25,  876, 96 - 50 , 73 });
	leftAnim[3].PushBack({ 96 * 2 + 25,  876, 96 - 50 , 73 });
	leftAnim[3].PushBack({ 96 * 3 + 25,   876, 96 - 50 , 73 });
	leftAnim[3].PushBack({ 96 * 4 + 25,   876, 96 - 50, 73 });
	leftAnim[3].PushBack({ 96 * 5 + 25,   876, 96 - 50 , 73 });
	leftAnim[3].speed = 0.1f;

	// FASE 3 Punch Attack
	punchAnim[3].PushBack({ 0 + 96 * 6 + 25, 876, 96 - 25, 73 });
	punchAnim[3].PushBack({ 0 + 96 * 7 + 25,  876, 96 - 25, 73 });
	punchAnim[3].speed = 0.2f;
	punchAnim[3].loop = false;

	// FASE 3 Crouch Punch Attack
	crouchpunchAnim[3].PushBack({ 92, 985 , 211-97, 50 });
	crouchpunchAnim[3].speed = 0.2f;
	crouchpunchAnim[3].loop = false;

	// FASE 3 Kick Attack
	kickAnim[3].PushBack({ 96 * 5 + 25,  950, 96 - 25 , 73 });
	kickAnim[3].speed = 0.2f;
	kickAnim[3].loop = false;

	// FASE 3 Crouch Kick Attack 
	crouchkickAnim[3].PushBack({ 96 * 5 + 25,  950, 96 - 25 , 73 });
	crouchkickAnim[3].speed = 0.2f;
	crouchkickAnim[3].loop = false;

	//FASE 3 stun
	stunAnim[3].PushBack({ 17, 1026,  53, 70 });
	stunAnim[3].PushBack({ 96 * 4 + 17, 1026, 53, 70 });
	stunAnim[3].speed = 0.05f;
	stunAnim[3].loop = false;

	//FASE 3 death
	deathAnim[3].PushBack({ 17, 1026,  53, 70 });
	deathAnim[3].PushBack({ 106,  1026, 177 - 106, 73 });
	deathAnim[3].PushBack({ 205, 1026, 278 - 205, 73 });
	deathAnim[3].speed = 0.02f;
	deathAnim[3].loop = false;


	punchWolfAnim.PushBack({ 0 + 96 * 6 + 25,950, 96 - 25 , 73 });



	gameOverAnim.PushBack({ 0 , 0 , 252, 44 });

	
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
	onBeastForm = false;
	gameOver = false;
	died = false;
	diedInAir = false;
	restartLevel = false;
	App->sceneLevel_1->isBoss = false;
	playerState = state::IDLE;

	texture = App->textures->Load("Assets/Sprites/fixedprotagonist+.png");
	nodesTexture = App->textures->Load("Assets/Sprites/lifeSprite2.png");
	uiTexture = App->textures->Load("Assets/Sprites/lifes.png");
	gameOverTexture = App->textures->Load("Assets/Sprites/endsCreen.png");
	currentAnimation = &idleAnim[0];

	laserFx = App->audio->LoadFx("Assets/Fx/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/Fx/explosion.wav");
	punchFx = App->audio->LoadFx("Assets/Fx/punch.wav");
	jumpFx = App->audio->LoadFx("Assets/Fx/jump.wav");
	playerDeathFx = App->audio->LoadFx("Assets/Fx/screamPlayerDeath.ogg");
	powerUpFx = App->audio->LoadFx("Assets/Fx/power.ogg");
	stunFx = App->audio->LoadFx("Assets/Fx/grunt.ogg");

	position.x = 20;
	position.y = 150;

	destroyed = false;

	collider = App->collisions->AddCollider({ position.x + 8, position.y + 8, 25, 70 }, Collider::Type::PLAYER, this);
	punch = App->collisions->AddCollider({ position.x + 20, position.y + 8, 0, 0 }, Collider::Type::PLAYER_ATTACK, this);
	punchWolf = App->collisions->AddCollider({ position.x + 20, position.y + 8, 0, 0 }, Collider::Type::PLAYER_ATTACK, this);
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

void ModulePlayer::WolfPunchTrigger()
{
	wolfPunch = true;
	punchWolfFlipType = flipType;
	wolfPunchPosition = position;
}


Update_Status ModulePlayer::Update()
{


	// Moving the player with the camera scroll

	GamePad& pad = App->input->pads[0];


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
	if (App->input->keys[SDL_SCANCODE_3] == Key_State::KEY_REPEAT)
	{
		phase = 3;
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

	//If Intro is pressed then restart the level
	if (App->input->keys[SDL_SCANCODE_RETURN] == Key_State::KEY_DOWN || pad.start == 1 && gameOver)
	{
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);
		if (score > highScore) {
			highScore = score;
		}
		destroyed = true;
		restartLevel = true;

	}

	//This is for checking if player is death (for no other imputs incoming)
	if (died) {
		playerState = state::DEATH;
	}

	if (wolfPunch) {
		counterForWolfPunch++;
		punchWolf->rect.w = 20;
		punchWolf->rect.h = 35;
		if (punchWolfFlipType)
		{
			punchWolf->SetPos(wolfPunchPosition.x + 20 - counterForWolfPunch * 6, wolfPunchPosition.y + 10);
		}
		else
		{
			punchWolf->SetPos(wolfPunchPosition.x + 40 + counterForWolfPunch * 6, wolfPunchPosition.y + 10);
		}
		if (counterForWolfPunch > 50) {
			punchWolf->rect.w = 0;
			punchWolf->rect.h = 0;
			wolfPunch = false;
			counterForWolfPunch = 0;
		}
	}

	

	switch (playerState) {
	case state::IDLE:
		currentAnimation = &idleAnim[phase];
		isInAColumn(62, 150, false);
		punch->rect.w = 0;
		punch->rect.h = 0;
		punch->SetPos(position.x + 20, -30);
		kick->rect.w = 0;
		kick->rect.h = 0;
		kick->SetPos(position.x + 20, -30);
		crouchkick->rect.w = 0;
		crouchkick->rect.h = 0;
		crouchkick->SetPos(position.x + 20, -30);
		collider->rect.w = 25;
		collider->rect.h = 70;
		collider->SetPos(position.x + 8, position.y);
		App->player->collider->PLAYER;
		if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN || pad.x == 1) {
			punchAnim[phase].Reset();
			playerState = state::PUNCH;
			App->audio->PlayFx(punchFx);

		}
		else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN || pad.b == 1)
		{
			kickAnim[phase].Reset();
			playerState = state::KICK;
			App->audio->PlayFx(punchFx);
		}
		else if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT
			|| pad.l_x < 0
			|| App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT
			|| pad.l_x > 0)
		{
			playerState = state::MOVEMENT;
		}
		else if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_DOWN
			|| (pad.l_x > -0.2f && pad.l_x < 0.2f && pad.l_y > 0)) {
			playerState = state::CROUCH;
		}
		else if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN || pad.a == 1) {
			playerState = state::JUMP;
		}
		break;
	case state::MOVEMENT:
		collider->SetPos(position.x + 8, position.y);
		punch->SetPos(position.x + 20, -30);
		kick->SetPos(position.x + 20, -30);
		crouchkick->SetPos(position.x + 20, -30);
		if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT || pad.l_x < 0) {
			punch->rect.w = 0;
			punch->rect.h = 0;
			kick->rect.w = 0;
			kick->rect.h = 0;
			crouchkick->rect.w = 0;
			crouchkick->rect.h = 0;
			position.x -= speed*2;
			isInAColumn(62, 150, false);
			collider->rect.h = 70;
			if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN || pad.a == 1)
			{
				jumpAnim[phase].Reset();
				playerState = state::JUMP;
			}
			else if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN || pad.x == 1)
			{
				punchAnim[phase].Reset();
				playerState = state::PUNCH;
				App->audio->PlayFx(punchFx);
			}
			else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN || pad.b == 1)
			{
				kickAnim[phase].Reset();
				playerState = state::KICK;
				App->audio->PlayFx(punchFx);
			}
			else if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_DOWN
				|| (pad.l_x > -0.2f && pad.l_x < 0.2f && pad.l_y > 0))
			{
				downAnim[phase].Reset();
				playerState = state::CROUCH;
			}
			else if (currentAnimation != &leftAnim[phase])
			{
				leftAnim[phase].Reset();
				flipType = true;
				currentAnimation = &leftAnim[phase];
			}
			leftAnim[phase].Update();
		}
		else if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT || pad.l_x > 0) {
			position.x += speed * 2;
			punch->rect.w = 0;
			punch->rect.h = 0;
			kick->rect.w = 0;
			kick->rect.h = 0;
			crouchkick->rect.w = 0;
			crouchkick->rect.h = 0;
			isInAColumn(62, 153, false);
			collider->rect.h = 70;
			if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN || pad.a == 1)
			{
				jumpAnim[phase].Reset();
				playerState = state::JUMP;
			}
			else if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN || pad.x == 1)
			{
				punchAnim[phase].Reset();
				playerState = state::PUNCH;
				App->audio->PlayFx(punchFx);
			}
			else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN || pad.b == 1)
			{
				kickAnim[phase].Reset();
				playerState = state::KICK;
				App->audio->PlayFx(punchFx);
			}
			else if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_DOWN
				|| (pad.l_x > -0.2f && pad.l_x < 0.2f && pad.l_y > 0))
			{
				downAnim[phase].Reset();
				currentAnimation = &downAnim[phase];
				playerState = state::CROUCH;
			}
			else if (currentAnimation != &rightAnim[phase])
			{
				rightAnim[phase].Reset();
				flipType = false;
				currentAnimation = &rightAnim[phase];
			}

			rightAnim[phase].Update();
		}
		else if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_IDLE
			|| App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_IDLE) {
			playerState = state::IDLE;
		}
		break;
	case state::CROUCH:
		if (damagedCrouch) {
			isInAColumn(62, 150, true);
			stunAnim[phase].Reset();
			damagedCrouch = false;
			playerState = state::STUNNED;
			break;

		}
		isInAColumn(90, 175, true);
		if (phase == 3) {
			collider->SetPos(position.x, position.y + 10);
			collider->rect.h = 45;
			collider->rect.w = 60;

		}
		else
		{
			collider->SetPos(position.x + 8, position.y + 10);

			collider->rect.h = 45;
		}

		if (currentAnimation != &downAnim[phase])
		{
			downAnim[phase].Reset();
			currentAnimation = &downAnim[phase];
		}
		downAnim[phase].Update();
		punch->rect.w = 0;
		punch->rect.h = 0;
		punch->SetPos(position.x + 20, -30);
		kick->rect.w = 0;
		kick->rect.h = 0;
		kick->SetPos(position.x + 20, -30);
		crouchkick->rect.w = 0;
		crouchkick->rect.h = 0;
		crouchkick->SetPos(position.x + 20, -30);
		if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN || pad.x == 1)
		{
			crouchpunchAnim[phase].Reset();
			playerState = state::CROUCH_PUNCH;
			App->audio->PlayFx(punchFx);
		}
		else if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN || pad.b == 1)
		{
			crouchkickAnim[phase].Reset();
			playerState = state::CROUCH_KICK;
			App->audio->PlayFx(punchFx);
		}
		else if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN || pad.a == 1)
		{
			playerState = state::JUMP;
		}
		else if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT || (pad.l_x > -0.2f && pad.l_x < 0.2f && pad.l_y > 0))
		{
			playerState = state::CROUCH;
		}
		else
		{
			playerState = state::IDLE;
		}
		break;
	case state::JUMP:
		if (diedInAir) {
			frame = 0;
			localJumpCounter = 0;
			damagedInAir = false;
			diedInAir = false;
			punchCounter = 0;
			kickCounter = 0;
			speedY = 16;
			deathAnim[phase].Reset();
			playerState = state::DEATH;
			break;
		}
		collider->SetPos(position.x + 8, position.y + 25);
		collider->rect.w = 25;
		collider->rect.h = 25;
		if (currentAnimation != &jumpAnim[phase])
		{
			jumpAnim[phase].Reset();
			currentAnimation = &jumpAnim[phase];
		}
		if (frame == 0)
		{
			App->audio->PlayFx(jumpFx);
		}
		jumpAnim[phase].Update();
		frame++;
		if (damagedInAir)
		{
			localJumpCounter++;
			currentAnimation = &stunAnim[phase];
			stunAnim[phase].Update();
			if (localJumpCounter >= 10)
			{
				//isInAColumn(62, 150, false);
				damagedInAir = false;
				frame -= localJumpCounter;
				localJumpCounter = 0;

			}


		}
		else
		{
			if ((App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT || pad.x == 1) && punchCounter < 3)
			{
				if (damagedInAir)
				{
					localJumpCounter++;
					currentAnimation = &stunAnim[phase];
					stunAnim[phase].Update();
					if (localJumpCounter >= 10)
					{
						//isInAColumn(62, 150, false);
						damagedInAir = false;
						localJumpCounter = 0;

					}
				}
				else
				{
					if (phase == 3) {
						WolfPunchTrigger();
					}
					punchCounter++;
					if (punchCounter == 1) {
						App->audio->PlayFx(punchFx);
					}
					currentAnimation = &punchAnim[phase];
					punchAnim[phase].Update();
					punch->rect.w = 42;
					punch->rect.h = 10;
					if (flipType)
					{
						punch->SetPos(position.x - 2, position.y + 8);
					}
					else
					{
						punch->SetPos(position.x + 20, position.y + 8);
					}

				}

			}
			else if ((App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT || pad.b == 1) && kickCounter < 3)
			{
				if (damagedInAir)
				{
					localJumpCounter++;
					currentAnimation = &stunAnim[phase];
					stunAnim[phase].Update();
					if (localJumpCounter >= 10)
					{
						//isInAColumn(62, 150, false);
						damagedInAir = false;
						frame -= localJumpCounter;
						localJumpCounter = 0;

					}
				}
				else
				{
					kickCounter++;
					if (kickCounter == 1) {
						App->audio->PlayFx(punchFx);
					}
					if (phase == 3)
					{
						if (flipType) {
							position.x -= 7;
						}
						else
						{
							position.x += 10;
						}

						currentAnimation = &kickAnim[phase];
						kickAnim[phase].Update();
						kick->rect.w = 60;
						kick->rect.h = 90;
						if (flipType)
						{
							kick->SetPos(position.x + 10, position.y);
						}
						else
						{
							kick->SetPos(position.x, position.y);
						}
					}
					else
					{
						currentAnimation = &kickAnim[phase];
						kickAnim[phase].Update();
						kick->rect.w = 45;
						kick->rect.h = 20;
						if (flipType)
						{
							kick->SetPos(position.x - 5, position.y + 35);
						}
						else
						{
							kick->SetPos(position.x + 20, position.y + 35);
						}
					}

				}


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
			else
			{
				punchCounter = 0;
				kickCounter = 0;
				frame = 0;
				speedY = 16;
				if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT || (pad.l_x > -0.2f && pad.l_x < 0.2f && pad.l_y > 0))
				{
					playerState = state::CROUCH;
				}
				else
				{
					playerState = state::IDLE;
				}

			}
		}
		break;
	case state::PUNCH:
		currentAnimation = &punchAnim[phase];
		punchAnim[phase].Update();
		frame++;
		punch->rect.w = 42;
		punch->rect.h = 10;
		if (flipType) {
			if (phase == 0) {
				collider->SetPos(position.x + 30-20, position.y);
				punch->SetPos(position.x - 2-20, position.y + 12);
			}
			else if (phase == 1) {
				collider->SetPos(position.x + 30-20, position.y);
				punch->SetPos(position.x - 2-20, position.y + 12);
			}
			else if (phase == 2) {
				collider->SetPos(position.x + 30-20, position.y);
				punch->SetPos(position.x - 2-25, position.y + 12);
			}
			else if (phase == 3) {

				collider->SetPos(position.x + 40, position.y);
				punch->SetPos(position.x - 2, position.y + 12);
				if (!wolfPunch)
				{
					WolfPunchTrigger();
				}


			}


		}
		else {
			collider->SetPos(position.x + 10, position.y);
			if (phase == 0 || phase == 1) {
				punch->SetPos(position.x + 20, position.y + 12);
			}
			else if (phase == 2)
			{
				punch->SetPos(position.x + 20, position.y + 12);
			}
			else if (phase == 3)
			{
				punch->SetPos(position.x + 20, position.y + 12);
				if (!wolfPunch)
				{
					WolfPunchTrigger();
				}
			}

		}
		if (frame >= 20)
		{
			playerState = state::IDLE;
			frame = 0;
		}
		break;

	case state::KICK:
		currentAnimation = &kickAnim[phase];
		kickAnim[phase].Update();
		frame++;
		kick->rect.w = 50;
		kick->rect.h = 20;
		if (flipType) {
			if (phase == 0)
			{
				collider->SetPos(position.x + 45-35, position.y);
				kick->SetPos(position.x + 20-45, position.y + 35);
			}
			else if (phase == 1) {
				collider->SetPos(position.x + 45-35, position.y);
				kick->SetPos(position.x + 20-45, position.y + 35);

			}
			else if (phase == 2) {
				collider->SetPos(position.x + 40-35, position.y);
				kick->SetPos(position.x + 20-55, position.y + 35);
			}
			else if (phase == 3) {
				position.x -= 2;
				collider->SetPos(position.x + 50, position.y);
				kick->SetPos(position.x + 20, position.y - 10);
				kick->rect.w = 60;
				kick->rect.h = 90;
			}

		}
		else {
			collider->SetPos(position.x + 10, position.y);
			if (phase == 0) {
				kick->SetPos(position.x + 20, position.y + 35);
			}
			else if (phase == 1) {
				collider->SetPos(position.x + 10, position.y);
				kick->SetPos(position.x + 30, position.y + 35);
				kick->rect.w = 60;
			}
			else if (phase == 2) {

				collider->SetPos(position.x + 10, position.y);
				kick->SetPos(position.x + 30, position.y + 35);
				kick->rect.w = 60;
			}
			else if (phase == 3) {
				position.x += 3;
				collider->SetPos(position.x + 10, position.y);
				kick->SetPos(position.x - 10, position.y - 10);
				kick->rect.w = 60;
				kick->rect.h = 90;
			}

		}
		if (frame >= 30)
		{
			if (phase == 3) {
				position.x += 10;
			}
			playerState = state::IDLE;
			frame = 0;
		}
		break;
	case state::CROUCH_PUNCH:
		if (damagedCrouch) {
			isInAColumn(62, 150, true);
			stunAnim[phase].Reset();
			damagedCrouch = false;
			playerState = state::STUNNED;
			break;

		}
		currentAnimation = &crouchpunchAnim[phase];
		crouchpunchAnim[phase].Update();
		frame++;
		isInAColumn(90, 180, true);

		punch->rect.w = 40;
		punch->rect.h = 10;
		if (flipType) {
			if (phase == 0) {
				collider->SetPos(position.x + 30-25, position.y + 5);
				punch->SetPos(position.x +2-20, position.y + 8);
			}
			else if (phase == 1) {
				collider->SetPos(position.x + 30-25, position.y + 5);
				punch->SetPos(position.x +2-20, position.y + 8);
			}
			else if (phase == 2) {
				collider->SetPos(position.x + 30-25, position.y + 5);
				punch->rect.h = 14;
				punch->SetPos(position.x +2-25, position.y + 2);
			}
			else if (phase == 3) {
				collider->SetPos(position.x + 30, position.y + 10);
				punch->SetPos(position.x - 20, position.y + 2);
				if (!wolfPunch)
				{
					WolfPunchTrigger();
				}
			}

		}
		else {
			collider->SetPos(position.x + 10, position.y);
			if (phase == 0) {
				punch->SetPos(position.x + 20, position.y + 8);
			}
			else if (phase == 1) {
				punch->rect.w = 50;
				punch->SetPos(position.x + 20, position.y + 8);
			}
			else if (phase == 2) {
				collider->SetPos(position.x + 30, position.y + 10);
				punch->rect.w = 50;
				punch->rect.h = 14;
				punch->SetPos(position.x + 50, position.y + 2);
			}
			else if (phase == 3) {

				collider->SetPos(position.x + 30, position.y + 10);
				punch->SetPos(position.x + 70, position.y + 2);
				if (!wolfPunch)
				{
					WolfPunchTrigger();
				}
			}

		}
		if (frame >= 10) {
			playerState = state::CROUCH;
			frame = 0;
		}
		break;
	case state::CROUCH_KICK:
		if (damagedCrouch) {
			isInAColumn(62, 150, true);
			stunAnim[phase].Reset();
			damagedCrouch = false;
			playerState = state::STUNNED;
			break;

		}
		currentAnimation = &crouchkickAnim[phase];
		crouchkickAnim[phase].Update();
		frame++;
		
		if (phase == 3) 
		{
			collider->rect.w = 25;
			collider->rect.h = 70;
			isInAColumn(62, 150, true);
			playerState = state::KICK;
			break;
		}
		else
		{
			isInAColumn(80, 165, true);
			crouchkick->rect.w = 18;
			crouchkick->rect.h = 40;
			if (flipType)
			{
				crouchkick->SetPos(position.x + 3, position.y - 2);
			}
			else
			{
				collider->SetPos(position.x + 10, position.y);
				crouchkick->SetPos(position.x + 25, position.y - 2);
			}
		}	
		if (frame >= 30)
		{
			if (phase == 3) {
				position.x -= 10;
			}
			playerState = state::CROUCH;
			frame = 0;
		}
		break;
	case state::STUNNED:
		currentAnimation = &stunAnim[phase];
		stunAnim[phase].Update();
		frame++;
		if (frame >= 20)
		{
			playerState = state::IDLE;
			frame = 0;
		}

		break;
	case state::DEATH:
		died = true;
		currentAnimation = &deathAnim[phase];
		if (App->sceneLevel_1->isBoss == false) {
			App->render->camera.x -= 1;
		}
		deathAnim[phase].Update();
		App->player->collider->NONE;

		frame++;
		
		if (frame < 10) {
			crouchkick->rect.w = 0;
			crouchkick->rect.h = 0;
			punch->rect.w = 0;
			punch->rect.h = 0;
			kick->rect.w = 0;
			kick->rect.h = 0;
			collider->rect.w = 0;
			collider->rect.h = 0;
			collider->SetPos(0, 0);
			position.y += 2;
			if (flipType) {
				position.x += 1;
			}
			else
			{
				position.x -= 1;
			}

		}
		else if (frame < 20)
		{
			position.y -= 2;
			if (flipType) {
				position.x += 1;
			}
			else
			{
				position.x -= 1;
			}

		}
		else if (frame >= 120)
		{
			if (gameOver) 
			{
				playerState = state::DEATH;
				frame = 20;
				died = false;
			}
			else
			{
				playerState = state::IDLE;
				frame = 0;
				died = false;
			}

		}

		break;


	}
	if (App->input->keys[SDL_SCANCODE_F2] == Key_State::KEY_DOWN) {
		GODMODE = !GODMODE;
	}
 

	if (App->input->keys[SDL_SCANCODE_M] == Key_State::KEY_DOWN) {
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneFinal, 90);

	}
	if (App->input->keys[SDL_SCANCODE_B] == Key_State::KEY_DOWN) {
		gameOver = true;
		died = true;
		deathAnim[phase].Reset();
		playerState = state::DEATH;
	}
	if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN) {
		App->sceneLevel_1->isBoss = true;
		App->enemies->AddEnemy(Enemy_Type::BOSS, App->render->camera.x + 180, 65);
		phase = 3;
	}


	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_IDLE
		&& playerState != state::PUNCH
		&& playerState != state::KICK
		&& playerState != state::JUMP
		&& playerState != state::STUNNED
		&& playerState != state::DEATH
		&& pad.l_x == 0
		&& pad.l_y == 0)
	{
		playerState = state::IDLE;
		
	}
	//If Punch state / crounch / punch crounch / crounch kick



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
	if (wolfPunch && phase == 3)
	{
		SDL_Rect rect = punchWolfAnim.GetCurrentFrame();
		if (punchWolfFlipType) {
			App->render->Blit(texture, wolfPunchPosition.x-20 - counterForWolfPunch * 6, wolfPunchPosition.y - 10, &rect, speed, punchWolfFlipType);
		}
		else
		{
			App->render->Blit(texture, wolfPunchPosition.x + 30 + counterForWolfPunch * 6, wolfPunchPosition.y - 10, &rect, speed, punchWolfFlipType);
		}

	}

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
		App->render->Blit(nodesTexture, 50 + 25 * i, 230, &rect, NULL, NULL, true);
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
		App->render->Blit(uiTexture, 10, 50, &rect, NULL, NULL, true);
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
	sprintf_s(highScoreText, 10, "%7d", highScore);

	// TODO 3: Blit the text of the score in at the bottom of the screen
	App->fonts->BlitText(0, 20, scoreFont, scoreText);
	App->fonts->BlitText(100, 20, scoreFont, highScoreText);
	secondsCounter++;
	if (secondsCounter % 100 == 0) {

		secondsCounter = 0;
	}
	else if (secondsCounter > 50) {
		App->fonts->BlitText(200, 20, scoreFont, "insert coin");
	}


	if (gameOver)
	{
		gameOverCounter++;
		if (gameOverCounter % 200 == 0) {

			gameOverCounter = 0;
		}
		else if (gameOverCounter > 60)
		{
			SDL_Rect rect = gameOverAnim.GetCurrentFrame();
			App->render->Blit(gameOverTexture, 30, 50, &rect, NULL, NULL, true);
		}

	}




	if (score >= 1000000) {
		position.x = 30;

	}

	if (LevelFinished) {
		App->textures->Unload(texture);
	}

	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::phaseUpdate() {

	if (phase == 0) {
		damage = 1;
	}
	else if (phase == 1) {
		damage = 2;
	}
	else if (phase == 2) {
		damage = 3;
	}
	else if (phase == 3) {
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
		lifeNodes--;

		damaged = true;
		PlayerTouch = false;
		if (lifeNodes <= 0)
		{
			App->audio->PlayFx(playerDeathFx);
			lifeNodes = 12;
			numLifes--;
			if (numLifes < 0)
			{
				gameOver = true;
			}
			if (playerState == state::JUMP)
			{
				diedInAir = true;
			}
			else
			{
				died = true;
				deathAnim[phase].Reset();
				playerState = state::DEATH;
			}


		}
		else
		{
			App->audio->PlayFx(stunFx);
			if (playerState == state::JUMP)
			{
				damagedInAir = true;
			}
			else if (playerState == state::CROUCH || playerState == state::CROUCH_KICK || playerState == state::CROUCH_PUNCH) {
				damagedCrouch = true;
			}
			else
			{
				stunAnim[phase].Reset();
				playerState = state::STUNNED;
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