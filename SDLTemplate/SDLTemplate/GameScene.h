#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "text.h"
#include "PowerUp.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();
private:
	Player* player;
	Enemy* enemy;

	//PowerUp
	float powerUpSpawnTimer;
	std::vector<PowerUp*> spawnedPowerUps;

	void spawnPowerUp();
	void PowerUpSpawnLogic();
	void PowerUpCollision();

	// Enemy spawning logic
	float spawnTime;
	float currentSpawnTimer;
	std::vector<Enemy*> spawnedEnemies;

	void spawnEnemies();
	void doSpawnLogic();

	void doCollisionLogic();
	void despawnEnemy(Enemy* enemy);

	int points;
};