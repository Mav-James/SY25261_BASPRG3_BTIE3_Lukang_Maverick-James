#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"

class Player : public GameObject
{
public:
	void start() override;
	void update() override;
	void draw() override;
private:
	int x;
	int y;
	int width;
	int height;

	SDL_Texture* texture;

	int speed;
	int acceleration;
	int defaultSpeed;
};

