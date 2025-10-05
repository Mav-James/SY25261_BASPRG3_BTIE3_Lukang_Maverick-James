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

	int getPositionX();
	int getPositionY();
	int getWidth();
	int getHeight();

	bool getIsAlive();
	void doDeath();
private:
	int x;
	int y;
	int height;
	int width;

	SDL_Texture* texture;

	float speed;

	float reloadTime;
	float currentReloadTime;

	Mix_Chunk* sound;
	std::vector<Bullet*> bullets;

	bool isAlive;
};

