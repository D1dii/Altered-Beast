#ifndef __FINAL__SCREEN_H__
#define __FINAL__SCREEN_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class FinalScreen : public Module {

public:
	FinalScreen(bool isEnabled);

	~FinalScreen();

	bool Start() override;

	Update_Status Update() override;

	Update_Status PostUpdate() override;

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* final;

	int frame = 0;
};
#endif
