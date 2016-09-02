//Hero.cpp

//Game includes
#include "Hero.h"
#include "Bullet.h"
#include "SSManager.h"

//Engine includes
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"


Hero::Hero()
{
    df::WorldManager &world_manager = df::WorldManager::getInstance();
    df::Vector p(7, world_manager.getBoundary().getVertical() / 4);
    setPosition(p);      

    //Reticle
    p_reticle = new Reticle();
    p_reticle->draw();

}

void Hero::fire(df::Vector target)
{
    //check if the limit has been exceeded
    if (fire_countdown > 0)
        return;
    fire_countdown = fire_slowdown;

    // Fire Bullet towards target.
    Bullet *p = new Bullet(getPosition());
    p->setVelocity(df::Vector(p->getVelocity().getX(),
        ((float)(target.getY() - getPosition().getY())) /
        ((float)(target.getX() - getPosition().getX()))));

    df::Vector gh = p->getVelocity();
    int y = gh.getY();
    //sound
    df::Sound *p_sound = df::ResourceManager::getInstance().getSound("fire");
    if (!p_sound)
    {
        df::LogManager &log_manager = df::LogManager::getInstance();
        log_manager.writeLog("Hero::fire(): Warning! Sound '%s' not found",
            "fire");
    }
    else
    {
        p_sound->play();
    }
}


//hero died, gameover
Hero::~Hero()
{
   
    SSManager::getInstance()->player1dies();

    df::WorldManager::getInstance().markForDelete(p_reticle);

}



/*int Hero::eventHandler(const df::Event *p_e)
{
if (p_e->getType() == df::STEP_EVENT)
{
step();
return 1;
}

return 0;
}

// Move on y axis
void Hero::move(int dy)
{
// See if time to move.
if (move_countdown > 0)
return;
move_countdown = move_slowdown;

// If stays on window, allow move.
df::Vector new_pos(getPosition().getX(), getPosition().getY() + dy);
df::WorldManager &world_manager = df::WorldManager::getInstance();
if ((new_pos.getY() > 3) &&
(new_pos.getY() < world_manager.getBoundary().getVertical()-1))
world_manager.moveObject(this, new_pos);
}

void Hero::fire(df::Vector target)
{
//check if the limit has been exceeded
if (fire_countdown > 0)
return;
fire_countdown = fire_slowdown;

// Fire Bullet towards target.
Bullet *p = new Bullet(getPosition());
p->setVelocity(df::Vector(p->getVelocity().getX(),
((float)(target.getY() - getPosition().getY())) /
((float)(target.getX() - getPosition().getX()))));

df::Vector gh = p->getVelocity();
int y = gh.getY();
//sound
df::Sound *p_sound = df::ResourceManager::getInstance().getSound("fire");
if (!p_sound)
{
df::LogManager &log_manager = df::LogManager::getInstance();
log_manager.writeLog("Hero::fire(): Warning! Sound '%s' not found",
"fire");
}
else
{
p_sound->play();
}
}

// Decrease rate restriction counters.
void Hero::step()
{
// Move countdown.
move_countdown--;
if (move_countdown < 0)
move_countdown = 0;

// Fire countdown.
fire_countdown--;
if (fire_countdown < 0)
fire_countdown = 0;
}*/