#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_scancode.h"


ModulePlayer::ModulePlayer()
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 35 , 12 + 280 * phase, 40, 75 });

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
	punchAnim.speed = 0.3f;
	punchAnim.loop = false;

	// Crouch Punch Attack
	crouchpunchAnim.PushBack({ 223, 181, 57, 37 });
	crouchpunchAnim.speed = 0.1f;
	crouchpunchAnim.loop = false;

	// Kick Attack


	// Crouch Kick Attack
	crouchkickAnim.PushBack({ 287, 188, 52, 30 });
	crouchkickAnim.PushBack({ 346, 165, 49, 53 });
	crouchkickAnim.speed = 0.3f;
	crouchkickAnim.loop = false;


}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/protagonist.png");

	currentAnimation = &idleAnim;

	laserFx = App->audio->LoadFx("Assets/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/explosion.wav");

	position.x = 20;
	position.y = 150;

	collider = App->collisions->AddCollider({ position.x + 8, position.y + 8, 20, 50 }, Collider::Type::PLAYER, this);
	punch = App->collisions->AddCollider({ position.x + 20, position.y + 8, 0, 0 }, Collider::Type::PLAYER_ATTACK, this);
	kick = App->collisions->AddCollider({ position.x + 20, position.y + 8, 0, 0 }, Collider::Type::PLAYER_ATTACK, this);
	

	return ret;
}

update_status ModulePlayer::Update()
{
	// Moving the player with the camera scroll

	if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
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

	if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
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
	if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_DOWN)
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

	if (App->input->keys[SDL_SCANCODE_0] == KEY_STATE::KEY_REPEAT)
	{
		phase = 0;
	}
	if (App->input->keys[SDL_SCANCODE_1] == KEY_STATE::KEY_REPEAT)
	{
		phase = 1;
	}
	if (App->input->keys[SDL_SCANCODE_2] == KEY_STATE::KEY_REPEAT)
	{
		phase = 2;
	}

	switch (playerState) {
	case state::IDLE:
		punch->rect.w = 0;
		punch->rect.h = 0;
		kick->rect.w = 0;
		kick->rect.h = 0;
		if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN) {
			punchAnim.Reset();
			playerState = state::PUNCH;
		}
		break;
		
	case state::MOVEMENT:
		if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN) 
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
		kick->rect.w = 0;
		kick->rect.h = 0;
		if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN) 
		{
			crouchpunchAnim.Reset();
			playerState = state::CROUCH_PUNCH;
		} 
		else if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_DOWN) 
		{
			crouchkickAnim.Reset();
			playerState = state::CROUCH_KICK;
		}

		break;
	case state::PUNCH:
		currentAnimation = &punchAnim;
		punchAnim.Update();
		frame++;
		punch->rect.w = 42;
		punch->rect.h = 10;
		if (frame >= 10) 
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
		kick->rect.x = position.x + 25;
		kick->rect.y = position.y - 2;
		kick->rect.w = 18;
		kick->rect.h = 40;
		if (frame >= 20) 
		{
			playerState = state::CROUCH;
			frame = 0;
		}
	}

	//This is for loading the new animations 
	idleAnim.PullBack(1);
	idleAnim.PushBack({ 35 , 12 + 280 * phase, 40, 75 });
	rightAnim.PullBack(3);
	rightAnim.PushBack({ 75, 12 + 280 * phase, 40, 75 });
	rightAnim.PushBack({ 125, 12 + 280 * phase, 40, 75 });
	rightAnim.PushBack({ 170, 12 + 280 * phase, 40, 75 });
	leftAnim.PullBack(3);
	leftAnim.PushBack({ 75, 12 + 280 * phase, 40, 75 });
	leftAnim.PushBack({ 125, 12 + 280 * phase, 40,75 });
	leftAnim.PushBack({ 170, 12 + 280 * phase, 40, 75 });
	punchAnim.PullBack(3);
	punchAnim.PushBack({ 7, 86 + 280 * phase, 52, 72 });
	punchAnim.PushBack({ 66, 87 + 280 * phase, 35, 72 });
	punchAnim.PushBack({ 107, 88 + 280 * phase, 61, 71 });





	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE
		&& playerState != state::PUNCH)
	{
		currentAnimation = &idleAnim;
		position.y = 150;
		collider->rect.h = 50;
		playerState = state::IDLE;
	}
	//If Punch state / crunch / punch crunch / crunch kick
	
	collider->SetPos(position.x + 8, position.y + 8);
	if (flipType) {
		punch->SetPos(position.x - 2, position.y + 8);
		kick->SetPos(position.x + 3, position.y - 2);
	}
	else {
		punch->SetPos(position.x + 20, position.y + 8);
		kick->SetPos(position.x + 25, position.y - 2);
	}

	currentAnimation->Update();

	if (destroyed)
	{
		destroyedCountdown--;
		if (destroyedCountdown <= 0)
			return update_status::UPDATE_STOP;
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();

		App->render->Blit(texture, position.x, position.y, &rect, speed, flipType);
	}

	

	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && destroyed == false && c2->type == collider->ENEMY)
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);

		App->audio->PlayFx(explosionFx);

		destroyed = true;
	}
	else if(c2->type == collider->SCREEN_LEFT)
	{
		position.x += 2;
	}
	else if (c2->type == collider->SCREEN_RIGHT)
	{
		position.x -= 2;
	}
}