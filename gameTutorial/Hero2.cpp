//Hero2.cpp

//Game includes
#include "Hero2.h"
#include "Bullet.h"
#include "SSManager.h"

//Engine includes
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"

Hero2::Hero2()
{
	// Link to "ship" sprite.
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();
	df::Sprite *p_temp_sprite;
	p_temp_sprite = resource_manager.getSprite("ship2");
	if (!p_temp_sprite)
	{
		log_manager.writeLog("Hero::Hero(): Warning! Sprite '%s' not found",
			"ship2");
	}
	else
	{		
		setSprite(p_temp_sprite);
		//setSpriteSlowdown(3);  // 1/3 speed animation.
		//setTransparency();	   // Transparent sprite.
	}
	
	df::WorldManager &world_manager = df::WorldManager::getInstance();
	df::Vector p(7, (3*world_manager.getBoundary().getVertical())/4);
	setPosition(p);	

}

void Hero2::fire()
{
	// Fire Bullet straight out

	//check if the limit has been exceeded
	if (fire_countdown > 0)
		return;	
	fire_countdown = fire_slowdown;

	Bullet *p = new Bullet(getPosition(), "bullet2");	

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
Hero2::~Hero2()
{
	SSManager::getInstance()->player2dies();

}



// Decrease rate restriction counters.
/*void Hero2::step()
{
	// Move countdown.
	move_countdown--;
	if (move_countdown < 0)
		move_countdown = 0;

	// Fire countdown.
	fire_countdown--;
	if (fire_countdown < 0)
		fire_countdown = 0;
}

int Hero2::eventHandler(const df::Event *p_e)
{
	if (p_e->getType() == df::STEP_EVENT)
	{
		step();
		return 1;
	}

	return 0;
}

// Move on y axis
void Hero2::move(int dy)
{
	// See if time to move.
	if (move_countdown > 0)
		return;
	move_countdown = move_slowdown;

	// If stays on window, allow move.
	df::Vector new_pos(getPosition().getX(), getPosition().getY() + dy);
	df::WorldManager &world_manager = df::WorldManager::getInstance();
	if ((new_pos.getY() > 3) &&
		(new_pos.getY() < world_manager.getBoundary().getVertical() - 1))
		world_manager.moveObject(this, new_pos);
}*/