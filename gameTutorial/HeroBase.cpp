//HeroBase.cpp

//Game includes
#include "Explosion.h"
#include "SSManager.h"
#include "HeroBase.h"

//Engine includes
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventStep.h"


HeroBase::HeroBase()
{
	// Link to "ship" sprite.
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();
	df::Sprite *p_temp_sprite;
	p_temp_sprite = resource_manager.getSprite("ship");
	if (!p_temp_sprite)
	{
		log_manager.writeLog("Hero::Hero(): Warning! Sprite '%s' not found",
			"ship");
	}
	else
	{
		setSprite(p_temp_sprite);
		setSpriteSlowdown(3);  // 1/3 speed animation.
		setTransparency();	   // Transparent sprite.

	}

	//interested events  
	registerInterest(df::STEP_EVENT);	

	setType("Hero");	

	//move speed
	move_slowdown = 2;
	move_countdown = move_slowdown;

	//fire limits
	fire_slowdown = 15;
	fire_countdown = fire_slowdown;	

}

int HeroBase::eventHandler(const df::Event *p_e)
{
	if (p_e->getType() == df::STEP_EVENT)
	{
		step();
		return 1;
	}

	return 0;
}

// Move on y axis
void HeroBase::move(int dy)
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
}


// Decrease rate restriction counters.
void HeroBase::step()
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

//hero died, gameover
HeroBase::~HeroBase()
{	

	for (int i = -8; i <= 8; i += 5)
	{
		for (int j = -5; j <= 5; j += 3)
		{
			df::Vector temp_pos = this->getPosition();
			temp_pos.setX(this->getPosition().getX() + i);
			temp_pos.setY(this->getPosition().getY() + j);
			Explosion *p_explosion = new Explosion;
			p_explosion->setPosition(temp_pos);
		}
	}
}