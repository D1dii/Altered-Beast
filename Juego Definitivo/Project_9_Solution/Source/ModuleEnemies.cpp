#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"

#include "Enemy.h"
#include "Enemy_Zombie.h"
#include "Enemy_NoSkull.h"
#include "Spirit_Ball.h"
#include "Enemy_Wolf.h"
#include "Enemy_Wolf_Blue.h"
#include "Enemy_Dragon.h"
#include "Enemy_Orco.h"
#include "Columns.h"
#include "Enemy_Boss.h"
#include "Boss_Head.h"


#define SPAWN_MARGIN 50


ModuleEnemies::ModuleEnemies(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies()
{

}

bool ModuleEnemies::Start()
{
	Enemy1 = App->textures->Load("Assets/Sprites/Zombie.png");
	Enemy2 = App->textures->Load("Assets/Sprites/NoSkull.png");
	Wolf = App->textures->Load("Assets/Sprites/Wolf.png");
	Wolf_Blue = App->textures->Load("Assets/Sprites/Wolf_Blue.png");
	Dragon = App->textures->Load("Assets/Sprites/Yellow_Dragon.png");
	Orco = App->textures->Load("Assets/Sprites/Orco.png");
	Item = App->textures->Load("Assets/Sprites/protagonist.png");
	Column = App->textures->Load("Assets/Sprites/newIntroTutorial.png");
	Boss = App->textures->Load("Assets/Sprites/Boss.png");
	enemyDestroyedFx = App->audio->LoadFx("Assets/Fx/explosion.wav");


	return true;
}


Update_Status ModuleEnemies::PreUpdate()
{
	// Remove all enemies scheduled for deletion
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->pendingToDelete)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleEnemies::Update()
{
	HandleEnemiesSpawn();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
			enemies[i]->Update();
	}

	HandleEnemiesDespawn();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleEnemies::PostUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Draw();
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(Enemy_Type type, int x, int y)
{
	bool ret = false;

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(spawnQueue[i].type == Enemy_Type::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::HandleEnemiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != Enemy_Type::NO_TYPE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			if (spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnEnemy(spawnQueue[i]);
				spawnQueue[i].type = Enemy_Type::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
		}
	}
}

void ModuleEnemies::HandleEnemiesDespawn()
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			// Delete the enemy when it has reached the end of the screen
			if (enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);

				enemies[i]->SetToDelete();
			}
		}
	}
}

void ModuleEnemies::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] == nullptr)
		{
			switch (info.type)
			{
				case Enemy_Type::ZOMBIE:
					enemies[i] = new Enemy_Zombie(info.x, info.y);
					enemies[i]->texture = Enemy1;
					break;
				case Enemy_Type::NO_SKULL:
					enemies[i] = new Enemy_NoSkull(info.x, info.y);
					enemies[i]->texture = Enemy2;
					break;
				case Enemy_Type::POWER_UP:
					enemies[i] = new Spirit_Ball(info.x, info.y);
					enemies[i]->texture = Item;
					break;
				case Enemy_Type::WOLF:
					enemies[i] = new Enemy_Wolf(info.x, info.y);
					enemies[i]->texture = Wolf;
					break;
				case Enemy_Type::WOLF_BLUE:
					enemies[i] = new Enemy_Wolf_Blue(info.x, info.y);
					enemies[i]->texture = Wolf_Blue;
					break;
				case Enemy_Type::DRAGON:
					enemies[i] = new Enemy_Dragon(info.x, info.y);
					enemies[i]->texture = Dragon;
					break;
				case Enemy_Type::ORCO:
					enemies[i] = new Enemy_Orco(info.x, info.y);
					enemies[i]->texture = Orco;
					break;
				case Enemy_Type::COLUMN:
					enemies[i] = new Columns(info.x, info.y);
					enemies[i]->texture = Column;
					break;
				case Enemy_Type::BOSS:
					enemies[i] = new Enemy_Boss(info.x, info.y);
					enemies[i]->texture = Boss;
					break;
				case Enemy_Type::BOSS_HEAD:
					enemies[i] = new Boss_Head(info.x, info.y);
					enemies[i]->texture = Boss;
					break;
			}
			
			enemies[i]->destroyedFx = enemyDestroyedFx;
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->OnCollision(c2); //Notify the enemy of a collision
			break;
		}
	}
}

void ModuleEnemies::RemoveColliders() 
{
	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (enemies[i] != nullptr) {

			App->collisions->RemoveCollider(enemies[i]->receiveDmg);
			App->collisions->RemoveCollider(enemies[i]->afflictDmg);
			App->collisions->RemoveCollider(enemies[i]->punchAttack);

		}
	}
}