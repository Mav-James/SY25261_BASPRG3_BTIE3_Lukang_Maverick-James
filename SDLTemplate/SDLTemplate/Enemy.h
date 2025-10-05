#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <vector>
#include "util.h"
#include "Player.h"

class Enemy : public GameObject
{
public:
	Enemy();
	~Enemy();
	void start();
	void update();
	void draw();

	void setPlayerTarget(Player* player);
	void setPosition(int x, int y);

	int getPositionX();
	int getPositionY();
	int getWidth();
	int getHeight();

private:
	int x;
	int y;
	float directionX;
	float directionY;
	int height;
	int width;

	float speed;

	SDL_Texture* texture;
	Mix_Chunk* sound;

	float reloadTime;
	float currentReloadTime;
	float directionChangeTime;
	float currentDirectionChangeTime;

	std::vector<Bullet*> bullets;
	Player* playerTarget;
};

