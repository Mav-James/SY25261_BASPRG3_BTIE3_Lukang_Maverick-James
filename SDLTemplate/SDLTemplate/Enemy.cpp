#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::start()
{
	texture = loadTexture("gfx/enemy.png");

	directionX = -1;
	directionY = 1;

	width = 0;
	height = 0;

	speed = 2;

	reloadTime = 60; // Reload time of 60 frames, or 1 second
	currentReloadTime = 0;

	directionChangeTime = (rand() % 300) + 180; // Direction change time of 3-8 seconds
	currentDirectionChangeTime = 0;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
	sound->volume = 64;
}

void Enemy::update()
{
	// Move
	x += directionX * speed;
	y += directionY * speed;

	// Basic AI, switch directions every X seconds
	if (currentDirectionChangeTime > 0)
		currentDirectionChangeTime--;

	if (currentDirectionChangeTime == 0)
	{
		// Flip directions
		directionY = -directionY;
		currentDirectionChangeTime = directionChangeTime;
	}

	// Decrement the enemy's reload timer
	if (currentReloadTime > 0)
		currentReloadTime--;

	// Only fire when our reload timer is ready
	if (currentReloadTime <= 0)
	{
		SoundManager::playSound(sound);

		float dx = -1;
		float dy = 0;

		calcSlope(playerTarget->getPositionX(), playerTarget->getPositionY(), x, y, &dx, &dy);

		Bullet* bullet = new Bullet(
			x, y - 2 + height / 2,
			dx, dy, 10,
			Side::ENEMY_SIDE);
		getScene()->addGameObject(bullet);

		bullets.push_back(bullet);

		// After firing, reset our reload timer
		currentReloadTime = reloadTime;
	}

	// Memory manage our bullets. When they go off screen, delete them
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionX() < 0)
		{
			// Cache the variable so we can delete it later [same as the linked list quiz in BASPRG2, where you put it in a variable and erase it]
			// We can�t delete it after erasing from the vector (leaked pointer)
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;
		}

		// We can�t mutate (change) our vector while looping inside it
		// this might crash on the next loop iteration
		// To counter that, we only delete one bullet per frame
		break;
	}
}

void Enemy::draw()
{
	blit(texture, x, y);
}

void Enemy::setPlayerTarget(Player* player)
{
	playerTarget = player;
}

void Enemy::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

int Enemy::getPositionX()
{
	return x;
}

int Enemy::getPositionY()
{
	return y;
}

int Enemy::getWidth()
{
	return width;
}

int Enemy::getHeight()
{
	return height;
}
