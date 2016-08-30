//Bullet.cpp

//Game includes
#include "Bullet.h"

//Engine includes
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventOut.h"

Bullet::Bullet(df::Vector hero_pos)
{	
	df::LogManager &log_manager = df::LogManager::getInstance();
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();	

	//assign bullet sprite
	df::Sprite *p_temp_sprite = resource_manager.getSprite("bullet");
	if (!p_temp_sprite)
	{
		log_manager.writeLog("Bullet::Bullet(): Warning! Sprite '%s' not found",
			"bullet");
	}
	else
	{
		setSprite(p_temp_sprite);
		setSpriteSlowdown(5);
	}

	// Set object type.
	setType("Bullet");

	// Set speed in horizontal direction.
	setVelocity(df::Vector(1, 0)); // 1 space left every 4 frames

									   
	df::Vector p(hero_pos.getX() + 3, hero_pos.getY()); //starts to the right of hero
	setPosition(p);


}

int Bullet::eventHandler(const df::Event * p_e)
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

	return 0;
}

void Bullet::out()
{
	df::WorldManager &world_manager = df::WorldManager::getInstance();
	world_manager.markForDelete(this);
}

void Bullet::hit(const df::EventCollision *p_collision_event)
{
	//if it hit a saucer or a saucer hit it.
	if ((p_collision_event->getObject1()->getType() == "Saucer") ||
		(p_collision_event->getObject2()->getType() == "Saucer")) 
	{
		df::WorldManager &world_manager = df::WorldManager::getInstance();
		world_manager.markForDelete(p_collision_event->getObject1());
		world_manager.markForDelete(p_collision_event->getObject2());
	}	
}