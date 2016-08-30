//Saucer.cpp

//game includes
#include "Saucer.h"
#include "Explosion.h"
#include "EventNuke.h"
#include "Points.h"

//engine includes
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventView.h"

//std includes
#include <stdlib.h> //rand

int Saucer::eventHandler(const df::Event * p_e)
{
    if (p_e->getType() == df::OUT_EVENT)
    {
        out();
        return 1;
    }
    else if (p_e->getType() == df::COLLISION_EVENT)
    {
        const df::EventCollision *p_collision_event =
            dynamic_cast <const df::EventCollision *> (p_e);
        hit(p_collision_event);
        return 1;
         
    }
    else if (p_e->getType() == NUKE_EVENT) 
    {		
        nuked();
        return 1;
    }

    return 0;
}

void Saucer::out()
{
    if (getPosition().getX() >= 0)
        return;

    moveToStart();
    new Saucer;
}

void Saucer::moveToStart()
{
    df::WorldManager &world_manager = df::WorldManager::getInstance();
    df::Vector temp_pos;

    float world_horiz = world_manager.getBoundary().getHorizontal();
    float world_vert = world_manager.getBoundary().getVertical();

    // x is off right 
    temp_pos.setX(world_horiz + rand() % (int)world_horiz + 3.0f);

    // vertical range
    temp_pos.setY(rand() % (int)(world_vert - 4) + 4.0f);

    // If collision, move right slightly until empty space.
    df::ObjectList collision_list = world_manager.isCollision(this, temp_pos);
    while (!collision_list.isEmpty())
    {
        temp_pos.setX(temp_pos.getX() + 1);
        collision_list = world_manager.isCollision(this, temp_pos);
    }

    world_manager.moveObject(this, temp_pos);
}

Saucer::Saucer()
{  
    df::LogManager &log_manager = df::LogManager::getInstance();
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();   

    // get saucer sprite.
    df::Sprite *p_temp_sprite = resource_manager.getSprite("saucer");
    if (!p_temp_sprite)
    {
        log_manager.writeLog("Saucer::Saucer(): Warning! Sprite '%s' not found",
            "saucer");
    }
    else
    {
        setSprite(p_temp_sprite);
        setSpriteSlowdown(4);
    }

    // Set object type.
    setType("Saucer");

    registerInterest(NUKE_EVENT);

    // Set speed in horizontal direction.
    setVelocity(df::Vector(-0.25, 0)); // 1 space left every 4 frames

    //randomize start
    moveToStart();

}

Saucer::~Saucer()
{
    df::EventView ev(POINTS_STRING, 10, true);
    df::WorldManager &world_manager = df::WorldManager::getInstance();
    world_manager.onEvent(&ev);
}

void Saucer::hit(const df::EventCollision *p_c) 
{
    
    if ((p_c->getObject1()->getType() == "Saucer") &&
        (p_c->getObject2()->getType() == "Saucer"))
        return;    
    else if ((p_c->getObject1()->getType() == "Bullet") ||
            (p_c->getObject2()->getType() == "Bullet"))
    {
        // Create an explosion.
        Explosion *p_explosion = new Explosion;
        p_explosion->setPosition(this->getPosition());		

        // Saucers appear stay around perpetually.
        new Saucer;
    }
    else if (((p_c->getObject1()->getType()) == "Hero") ||
            ((p_c->getObject2()->getType()) == "Hero")) 
    {
            df::WorldManager &world_manager = df::WorldManager::getInstance();
            world_manager.markForDelete(p_c->getObject1());
            world_manager.markForDelete(p_c->getObject2());
    }
    
    //sound
    df::Sound *p_sound = df::ResourceManager::getInstance().getSound("explode");
    p_sound->play();

}

void Saucer::nuked()
{
    Explosion *p_explosion = new Explosion;
    p_explosion->setPosition(this->getPosition());

    df::WorldManager &world_manager = df::WorldManager::getInstance();
    world_manager.markForDelete(this);

    new Saucer;
}