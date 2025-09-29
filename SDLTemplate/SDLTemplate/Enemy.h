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
private:
	int x;
	int y;
	float directionX;
	float directionY;
	int width;
	int height;

	SDL_Texture* texture;
	Mix_Chunk* sound;
	Player* PlayerTarget;

	int speed;
	int acceleration;
	int defaultSpeed;
	float reloadTime;
	float currentReloadTime;
	float directionChangeTime;
	float currentDirectionChangeTime;
	std::vector<Bullet*> bullets;
};

