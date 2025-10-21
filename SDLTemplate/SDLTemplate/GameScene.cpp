#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player);

	boss =	NULL;
	bossSpawned = false;
}

GameScene::~GameScene()
{
	delete player;
	if (boss != NULL)
	{
		delete boss;
		boss = NULL;
	}
}

void GameScene::start()
{
	Scene::start();
	// Initialize any scene logic here

	spawnTime = 300; // Spawn time of 5 seconds
	currentSpawnTimer = spawnTime;

	for (int i = 0; i < 3; i++)
	{
		spawnEnemies();
	}

	initFonts();

	points = 0;

	powerUpSpawnTimer = 300; // spawn every 5 seconds



}

void GameScene::draw()
{
	Scene::draw();

	if (player->getIsAlive())
	{
		drawText(110, 20, 255, 255, 255, TEXT_CENTER, "POINTS: %03d", points);
	}
	else
	{
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 255, 0, 0, TEXT_CENTER, "GAME OVER!");
	}

	// Draws boss if getting spawned

	if (bossSpawned && boss != NULL)
	{
		boss->draw(app.renderer);
	}
}

void GameScene::update()
{
	Scene::update();

	doSpawnLogic();
	doCollisionLogic();
	PowerUpSpawnLogic();
	PowerUpCollision();

	//Spawns boss when it reaches a specific amount of points
	if (points >= 2000 && !bossSpawned)
	{
		spawnBoss();
	}

	
	if (bossSpawned && boss != NULL)
	{
		boss->update();
	}
}

void GameScene::spawnPowerUp()
{
	int randomX = rand() % (SCREEN_WIDTH - 64);
	PowerUp* powerUp = new PowerUp(randomX, 0);
	addGameObject(powerUp);
	spawnedPowerUps.push_back(powerUp);
}

void GameScene::PowerUpSpawnLogic()
{
	if (powerUpSpawnTimer > 0)
		powerUpSpawnTimer--;
	else
	{
		spawnPowerUp();
		powerUpSpawnTimer = 300 + rand() % 100; // random delay
	}
}

void GameScene::PowerUpCollision()
{
	for (int i = 0; i < spawnedPowerUps.size(); i++)
	{
		PowerUp* p = spawnedPowerUps[i];
		int collision = checkCollision(
			player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
			p->getPositionX(), p->getPositionY(), p->getWidth(), p->getHeight()
		);

		if (collision == 1)
		{
			player->increasePowerLevel();
			std::cout << "Power-up collected! Level: " << player->getPowerLevel() << std::endl;

			spawnedPowerUps.erase(spawnedPowerUps.begin() + i);
			delete p;
			break;
		}
	}
}

void GameScene::spawnEnemies()
{
	Enemy* enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->setPlayerTarget(player);

	enemy->setPosition(1200, 300 + (rand() % 300));
	spawnedEnemies.push_back(enemy);
}

void GameScene::doSpawnLogic()
{
	if (currentSpawnTimer > 0)
		currentSpawnTimer--;

	if (currentSpawnTimer <= 0)
	{
		for (int i = 0; i < 3; i++)
		{
			spawnEnemies();
		}

		currentSpawnTimer = spawnTime;
	}
}

void GameScene::doCollisionLogic()
{
	for (int i = 0; i < objects.size(); i++)
	{
		Bullet* bullet = dynamic_cast<Bullet*>(objects[i]);

		// Check if the cast was successful
		if (bullet != NULL)
		{
			if (bullet->getSide() == Side::ENEMY_SIDE)
			{
				int collision = checkCollision(
					player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
					bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
				);

				if (collision == 1 && player->getIsAlive())
				{
					std::cout << "Player is hit!" << std::endl;
					player->doDeath();
					break;
				}
			}
			else if (bullet->getSide() == Side::PLAYER_SIDE)
			{
				for (int i = 0; i < spawnedEnemies.size(); i++)
				{
					Enemy* currentEnemy = spawnedEnemies[i];

					int collision = checkCollision(
						currentEnemy->getPositionX(), currentEnemy->getPositionY(), currentEnemy->getWidth(), currentEnemy->getHeight(),
						bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
					);

					if (collision == 1)
					{
						std::cout << "Enemy is hit!" << std::endl;
						despawnEnemy(currentEnemy);

						points++;
						break;
					}
				}
			}
		}
	}
}

void GameScene::despawnEnemy(Enemy* enemy)
{
	int index = -1;

	for (int i = 0; i < spawnedEnemies.size(); i++)
	{
		if (spawnedEnemies[i] == enemy)
		{
			index = i;
			break;
		}
	}

	if (index > -1)
	{
		spawnedEnemies.erase(spawnedEnemies.begin() + index);
		delete enemy;
	}
}

void GameScene::spawnBoss()
{
	boss = new Boss();
	boss->start(app.renderer);
	boss->setPosition(500, 50); // Spawn near top of screen
	bossSpawned = true;
}
