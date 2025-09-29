#include "Enemy.h"
#include "Scene.h"




Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::start()
{
	// Load Texture
	texture = loadTexture("gfx/enemy.png");


	// Initialize to avoid garbage values
	directionX = -1;
	directionY = 1;
	x = 1000;
	y = 500;
	width = 0;
	height = 0;

	defaultSpeed = 2;
	acceleration = 5;
	speed = defaultSpeed; 
	reloadTime = 60;
	currentReloadTime = 0;
	directionChangeTime = (rand() % 300) + 180;
	currentDirectionChangeTime = 0;

	// Query the texture to set our width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
}

void Enemy::update()
{
	x += directionX * speed;
	y += directionY * speed;

	if (currentDirectionChangeTime > 0)
		currentDirectionChangeTime--;

	if (currentDirectionChangeTime == 0)
	{
		directionY = -directionY;
		currentDirectionChangeTime = directionChangeTime;
	}

	if (currentReloadTime > 0);
	currentReloadTime--;

	if (currentReloadTime == 0)

	{
		float dx = -1;
		float dy = 0;

		calcSlope(PlayerTarget->getPositionX(), PlayerTarget->getPositionY(), x, y, &dx, &dy);

		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x + width, y - 2 + height / 2, -1, 0, 10);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
		

		currentReloadTime = reloadTime;
	}

	// Memory manage our bullets. When they go off screen, deleate them
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionX() < 0)
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


void Enemy::draw()
{
	blit(texture, x, y);
}

void Enemy::setPlayerTarget(Player* player)
{
	PlayerTarget = player;
}
