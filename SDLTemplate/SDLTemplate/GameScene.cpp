#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player);
}

GameScene::~GameScene()
{
	delete player;
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
}

void GameScene::update()
{
	Scene::update();

	doSpawnLogic();
	doCollisionLogic();
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
