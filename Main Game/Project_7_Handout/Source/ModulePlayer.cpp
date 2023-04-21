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
	idleAnim.PushBack({ 35 , 12, 40, 75 });

	// Move down
	downAnim.PushBack({ 183, 176, 34, 43});
	downAnim.loop = false;
	downAnim.speed = 0.1f;
	
	// Move right
	rightAnim.PushBack({75, 12, 40, 75});
	rightAnim.PushBack({ 125, 12, 40, 75 });
	rightAnim.PushBack({ 170, 12, 40, 75 });
	rightAnim.speed = 0.1f;
	rightAnim.speed = 0.1f;
	
	// Move left 
	leftAnim.PushBack({ 75, 12, 40, 75 });
	leftAnim.PushBack({ 125, 12, 40,75 });
	leftAnim.PushBack({ 170, 12, 40, 75 });
	leftAnim.speed = 0.1f;

	// Punch Attack
	punchAnim.PushBack({ 7, 86, 52, 72 });
	punchAnim.PushBack({ 66, 87, 35, 72 });
	punchAnim.PushBack({ 107, 88, 61, 71 });
	punchAnim.speed = 0.1f;
	punchAnim.loop = false;
	
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

	return ret;
}

update_status ModulePlayer::Update()
{
	// Moving the player with the camera scroll

	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		position.x -= speed;
		position.y = 150;
		collider->rect.h = 50;
		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			flipType = true;
			currentAnimation = &leftAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		position.x += speed;
		position.y = 150;
		collider->rect.h = 50;
		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			flipType = false;
			currentAnimation = &rightAnim;
		}
	}
	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		position.y = 175;
		collider->rect.h = 25;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		if (currentAnimation != &punchAnim) {
			punchAnim.Reset();
			currentAnimation = &punchAnim;
		}
		
	}
	
	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE:: KEY_IDLE) {
		currentAnimation = &idleAnim;
		position.y = 150;
		collider->rect.h = 50;
	}

	


	collider->SetPos(position.x + 8, position.y + 8);

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
	if (c1 == collider && destroyed == false)
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);

		App->audio->PlayFx(explosionFx);

		destroyed = true;
	}
}