#include "Boss_Head3.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "time.h"

Boss_Head3::Boss_Head3(int x, int y) : Enemy(x, y) {

	// Launch Animation
	launchAnim.PushBack({ 150, 372, 46, 47 });
	currentAnim = &launchAnim;

	// Attack animation
	attackAnim.PushBack({ 204, 354, 46, 47 });

	// Death animation
	deathAnim.PushBack({ 200, 403, 54, 44 });
	deathAnim.PushBack({ 199, 458, 54, 44 });
	deathAnim.PushBack({ 203, 510, 54, 44 });

	LaunchPath.PushBack({ -2.0f, -0.75f }, 30, &launchAnim);
	attackPath.PushBack({ 0.0f, 1.5f }, 30, &attackAnim);

}

void Boss_Head3::Update() {

	srand(time(NULL));

	if (randomPos == 0) {
		randomPos = rand() % (3) + 1;
	}

	if (randomPos == 1) {
		limitFrames = 50;
	}
	else if (randomPos == 2) {
		limitFrames = 75;
	}
	else if (randomPos == 3) {
		limitFrames = 100;
	}

	switch (headState)
	{
	case Boss_Head3::state::LAUNCH:
		currentAnim = &launchAnim;
		launchAnim.Update();
		frame++;
		LaunchPath.Update();
		position = spawnPos + LaunchPath.GetRelativePosition();
		if (frame >= limitFrames) {
			frame = 0;
			spawnPos.x = position.x;
			spawnPos.y = position.y;
			headState = state::ATTACK;
		}
		break;
	case Boss_Head3::state::ATTACK:
		currentAnim = &attackAnim;
		attackAnim.Update();
		attackPath.Update();
		position = spawnPos + attackPath.GetRelativePosition();
		break;
	case Boss_Head3::state::DEATH:
		currentAnim = &deathAnim;
		deathAnim.Update();
		break;

	}

}

void Boss_Head3::OnCollision(Collider* col) {

}

void Boss_Head3::SetToDelete() {

}