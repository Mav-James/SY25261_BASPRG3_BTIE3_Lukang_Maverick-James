#include "PowerUp.h"

PowerUp::PowerUp(int startX, int startY)
{
    x = startX;
    y = startY;
}

PowerUp::~PowerUp()
{
}

void PowerUp::start()
{
    texture = loadTexture("gfx/powerup.png");
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    speed = 2;
}

void PowerUp::update()
{
    y += speed;

    // Despawn when out of screen
    if (y > SCREEN_HEIGHT)
    {
        // setIsActive(false);
    }
}

void PowerUp::draw()
{
    blitScale(texture, x, y, &width, &height, 1.5);
}

int PowerUp::getPositionX() { return x; }
int PowerUp::getPositionY() { return y; }
int PowerUp::getWidth() { return width; }
int PowerUp::getHeight() { return height; }

