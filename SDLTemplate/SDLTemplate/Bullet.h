#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"

enum class Side
{
	PLAYER_SIDE,
	ENEMY_SIDE
};

class Bullet : public GameObject
{
public:
	Bullet(int positionX, int positionY, float directionX, float directionY, float speed, Side side);
	void start() override;
	void update() override;
	void draw() override;

	int getPositionX();
	int getPositionY();
	int getWidth();
	int getHeight();

	Side getSide();
private:
	int x;
	int y;
	int height;
	int width;

	SDL_Texture* texture;

	float speed;
	float directionX;
	float directionY;

	Side side;
};

