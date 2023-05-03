#ifndef __INITIAL__SCREEN_H__
#define __INITIAL__SCREEN_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class Initial_Screen :public Module {

	Initial_Screen(bool startEnabled);

	~Initial_Screen();

	bool Start() override;

	Update_Status Update() override;

	Update_Status PostUpdate() override;

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* intro;

	int frame = 0;
};
#endif