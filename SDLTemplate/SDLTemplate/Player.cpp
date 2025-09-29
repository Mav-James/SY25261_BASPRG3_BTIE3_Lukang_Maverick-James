#include "Player.h"
#include "Scene.h"

Player::~Player()
{
	// Memory manage our bullets. Deleate all bullets on player deletetion/death
	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}
	bullets.clear();
}

void Player::start()
{
	// Load Texture
	texture = loadTexture("gfx/player.png");


	// Initialize to avoid garbage values
	x = 100;
	y = 100;
	width = 0;
	height = 0;

	defaultSpeed = 2;
	acceleration = 5;
	speed = defaultSpeed;
	reloadTime = 8;
	currentReloadTime = 0;

	// Query the texture to set our width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
}

void Player::draw()
{
	blit(texture, x, y);
}



void Player::update()
{
	if (app.keyboard[SDL_SCANCODE_LSHIFT])
	{
		speed = acceleration;

	}

	if (app.keyboard[SDL_SCANCODE_BACKSPACE])
	{
		speed = defaultSpeed;
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

	// Decrement the player's reload timer
	if (currentReloadTime > 0);
	    currentReloadTime --;


	if (app.keyboard[SDL_SCANCODE_F])
	{
		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x + width, y - 2 + height / 2, 1, 0, 10);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
		

		currentReloadTime = reloadTime;
	}
	// Memory manage our bullets. When they go off screen, deleate them
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionX() > SCREEN_WIDTH)
		{
			// Cache the variable so we can deleate it later
		   // We can't delete it after erasing from the vector (leaked pointer)
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;



			// We can't mutate (change) our vector while looping inside it
		   // this might crash on the next loop iteration
		  // To encounter that, we only delete one bullet per frame
			break;
		}
	}
}

	

	int Player::getPositionX()
	{
		return x;
	}

	int Player::getPositionY()
	{
		return y;
	}
