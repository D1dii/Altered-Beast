#ifndef __INITIAL_CUTSCENE_H__
#define __INITIAL_CUTSCENE_H__

#include "Animation.h"
#include "Module.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"

class Initial_Cutscene : public Module
{
public:
	//Constructor
	Initial_Cutscene(bool startEnabled);

	//Destructor
	~Initial_Cutscene();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	// Disables the player and the enemies
	bool CleanUp();

public:

	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgbackTexture = nullptr;
	SDL_Texture* bgfrontTexture = nullptr;
	SDL_Texture* initialScreen = nullptr;

	// The sprite rectangle for the ground


	Collider* bgfront;
	Collider* bgleft;
	Collider* bgright;

	int frame = 0;
	uint beastHowl = 0;


};


#endif // __INITIAL_CUTSCENE_H__