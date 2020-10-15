#pragma once

#include "Scene.h"

class JellyPlatforms : public Scene
{
public:
	JellyPlatforms(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;

	void MovingPlatform(float pos1, float y);

	void Update() override;

	//Input overrides
	void KeyboardHold() override;
	void KeyboardDown() override;
	void KeyboardUp() override;

protected:
	bool onGround = false;
	bool canJump = false;
	int platform = 0;
	bool movingRight = true;
};