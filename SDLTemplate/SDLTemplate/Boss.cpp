#include "Boss.h"


Boss::Boss() {}

Boss::~Boss() {}

void Boss::start(SDL_Renderer* renderer)
{
    texture = loadTexture("gfx/powerup.png");
    sound = SoundManager::loadSound("sound/boss_attack.ogg");

    directionX = -1;
    directionY = 1;
    speed = 1;
    hp = 500;
    attackCooldown = 120;
    currentAttackTime = 0;

    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Boss::update()
{
    x += directionX * speed;
    y += directionY * speed;

    if (x < 0 || x + width > 800)
        directionX = -directionX;

    if (y < 0 || y + height > 600)
        directionY = -directionY;

    if (currentAttackTime > 0)
        currentAttackTime--;
    else
    {
        
        SoundManager::playSound(sound);

        Bullet* bullet = new Bullet(
            x + width / 2,        
            y + height,           
            0, 1,                 
            8,                    
            Side::ENEMY_SIDE      
        );
        bullets.push_back(bullet);

        currentAttackTime = attackCooldown;

        for (int i = 0; i < bullets.size(); i++)
        {
            bullets[i]->update();
        }

        // Memory manage our bullets. When they go off screen, delete them
        for (int i = 0; i < bullets.size(); i++)
        {
            if (bullets[i]->getPositionX() < 0)
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
    }
}

void Boss::draw(SDL_Renderer* renderer)
{
    SDL_Rect dst = { x, y, width, height };
    SDL_RenderCopy(renderer, texture, NULL, &dst);
}

void Boss::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}

bool Boss::isDefeated()
{
    return hp <= 0;
}
