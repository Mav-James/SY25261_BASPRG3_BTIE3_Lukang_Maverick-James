#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
<<<<<<< HEAD
	player = new Player();
	this->addGameObject(player);

=======
>>>>>>> 3f8d0e749e16566bf24e8943dae44e0aea0b1e03
}

GameScene::~GameScene()
{

}

void GameScene::start()
{
	Scene::start();
	// Initialize any scene logic here
}

void GameScene::draw()
{
	Scene::draw();
}

void GameScene::update()
{
	Scene::update();
}
