#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <vector>

class Player : public GameObject
{
public:
	~Player();
	void start();
	void update();
	void draw();
private:
	int x;
	int y;
	int width;
	int height;

	SDL_Texture* texture;
	Mix_Chunk* sound;

	int speed;
	int acceleration;
	int defaultSpeed;
	float reloadTime;
	float currentReloadTime;
	std::vector<Bullet*> bullets;
};

