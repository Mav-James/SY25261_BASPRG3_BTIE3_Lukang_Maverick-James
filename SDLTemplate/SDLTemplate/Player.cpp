#include "Player.h"
#include "Player.h"
#include "Player.h"
#include "Player.h"


Player::~Player()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionX() > SCREEN_WIDTH)
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

	bullets.clear();
}

void Player::start()
{
	texture = loadTexture("gfx/player.png");

	y = 100;
	x = 100;

	width = 0;
	height = 0;

	speed = 4;

	powerlevel = 1;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");

	reloadTime = 4; // Reload time of 8 frames, or 0.13 seconds
	currentReloadTime = 0;

	isAlive = true;
}

void Player::update()
{
	// Memory manage our bullets. When they go off screen, delete them
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionX() > SCREEN_WIDTH)
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

	if (!isAlive)
	{
		return;
	}

	if (app.keyboard[SDL_SCANCODE_W])
	{
		y -= speed;
	}

	if (app.keyboard[SDL_SCANCODE_S])
	{
		y += speed;
	}

	if (app.keyboard[SDL_SCANCODE_A])
	{
		x -= speed;
	}

	if (app.keyboard[SDL_SCANCODE_D])
	{
		x += speed;
	}

	if (currentReloadTime > 0)
		currentReloadTime--;

	if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime <= 0)
	{
		SoundManager::playSound(sound);

		
		Bullet* bullet = new Bullet(x + width, y - 2 + height / 2, 1, 0, 10, Side::PLAYER_SIDE);
		getScene()->addGameObject(bullet);
		bullets.push_back(bullet);

		
		if (powerLevel >= 2)
		{
			Bullet* bulletUp = new Bullet(x + width, y - 10, 1, -0.1, 10, Side::PLAYER_SIDE);
			getScene()->addGameObject(bulletUp);
			bullets.push_back(bulletUp);
		}

		if (powerLevel >= 3)
		{
			Bullet* bulletDown = new Bullet(x + width, y + 10, 1, 0.1, 10, Side::PLAYER_SIDE);
			getScene()->addGameObject(bulletDown);
			bullets.push_back(bulletDown);
		}

		currentReloadTime = reloadTime;
	}

}

void Player::draw()
{
	if (!isAlive)
	{
		return;
	}

	blitScale(texture, x, y, &width, &height, 2);
}

void Player::increasePowerlevel()
{
	if (powerLevel < 3)
		powerlevel++;
}

int Player::getPowerlevel()
{
	return powerlevel;
}

int Player::getPositionX()
{
	return x;
}

int Player::getPositionY()
{
	return y;
}

int Player::getWidth()
{
	return width;
}

int Player::getHeight()
{
	return height;
}

bool Player::getIsAlive()
{
	return isAlive;
}

void Player::doDeath()
{
	isAlive = false;
}

void Player::increasePowerLevel()
{
	if (powerLevel < 3) // limit max to 3 lines of fire
		powerLevel++;
}

int Player::getPowerLevel()
{
	return 0;
}

int Player::powerlevel()
{
	return powerlevel;
}
