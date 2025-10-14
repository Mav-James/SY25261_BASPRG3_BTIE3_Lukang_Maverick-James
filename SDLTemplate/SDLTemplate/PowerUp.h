#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include <SDL.h>

class PowerUp : public GameObject
{
public:
    PowerUp(int startX, int startY);
    ~PowerUp();
    void start();
    void update();
    void draw();

    int getPositionX();
    int getPositionY();
    int getWidth();
    int getHeight();

private:
    SDL_Texture* texture;
    int x, y;
    int width, height;
    float speed;
};


