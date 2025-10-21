#pragma once
#include <SDL.h>
#include "SoundManager.h"
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include "Scene.h"
#include <vector>
#include "util.h"
#include "Player.h"

class Boss
{
private:
    SDL_Texture* texture;
    Mix_Chunk* sound;

    int x, y;
    int width, height;
    int directionX, directionY;
    int speed;
    int hp;
    int attackCooldown;
    int currentAttackTime;

    std::vector<Bullet*> bullets;

public:
    Boss();
    ~Boss();

    void start(SDL_Renderer* renderer);
    void update();
    void draw(SDL_Renderer* renderer);

    void setPosition(int x, int y);
    bool isDefeated();
};
