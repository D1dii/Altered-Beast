#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;

	void phaseUpdate();

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	void isInAColumn(int posInColumn, int pos, int wasInColumn)
	{
		if (inAColumn)
		{
			position.y = posInColumn;
			if (!wasInColumn)
			{
				inAColumn = false;
			}

		}
		else
		{
			position.y = pos;
		}

	}

public:
	// Position of the player in the map
	iPoint position;

	// The speed in which we move the player (pixels per frame)
	int speed = 1;
	int punchCounter = 0;
	int kickCounter = 0;
	// Jumping
	int speedY = 16;
	int gravity = -1;

	// Player Form
	int phase = 0;

	// Attacks Damage
	int damage = 1;
	
	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	SDL_Texture* nodesTexture = nullptr;
	SDL_Texture* uiTexture = nullptr;

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;
	Animation* currentLifeAnimation = nullptr;

	// A set of animations
	Animation idleAnim[4];
	Animation downAnim[4];
	Animation leftAnim[4];
	Animation rightAnim[4];
	Animation punchAnim[4];
	Animation kickAnim[4];
	Animation crouchpunchAnim[4];
	Animation crouchkickAnim[4];
	Animation jumpAnim[4];
	Animation stunAnim[4];
	Animation deathAnim[4];
	Animation nodesAnim[4];
	Animation lifesAnim[3];


	//States of Player

	enum class state
	{
		IDLE,
		MOVEMENT,
		JUMP,
		CROUCH,
		PUNCH,
		CROUCH_PUNCH,
		KICK,
		CROUCH_KICK,
		JUMP_PUNCH,
		JUMP_KICK,
		STUNNED,
		POWER_UP,
		DEATH,
	};
	
	state playerState = state::IDLE;

	bool GODMODE = false;
	bool damaged = false;
	bool PlayerTouch = true;
	bool LevelFinished = false;
	int localJumpCounter = 0;
	bool damagedInAir = false;
	bool damagedCrouch = false;
	bool diedInAir = false;
	bool died = false;
	int frame = 0;
	int waitForDmg = 0;
	int numLifes = 2;
	int lifeNodes = 12;

	// The player's collider
	Collider* collider = nullptr;
	Collider* punch = nullptr;
	Collider* crouchkick = nullptr;
	Collider* kick = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	// A flag to detect if the player is flipped
	bool flipType;
	

	// Sound effects indices
	uint laserFx = 0;
	uint explosionFx = 0;
	uint punchFx = 0;
	uint jumpFx = 0;
	uint playerDeathFx = 0;
	uint powerUpFx = 0;

	// Font score index
	uint score = 000;
	int scoreFont = -1;
	char scoreText[10] = { "\0" };
	int secondsCounter = 0;
	bool inAColumn = false;
};

#endif //!__MODULE_PLAYER_H__