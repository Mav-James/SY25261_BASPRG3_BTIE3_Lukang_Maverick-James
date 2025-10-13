#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"


class Bullet : public GameObject
{
public:
	Bullet(int positionX, int positionY, float directionX, float directionY, float speed);
	void start() override;
	void update() override;
	void draw() override;
	int getPositionX();
	int getPositionY();
	int getWidth();
	int getHeight();
private:
	int x;
	int y;
	int height;
	int width;
	int speed;
	float directionX;
	float directionY;

	SDL_Texture* texture;

};
