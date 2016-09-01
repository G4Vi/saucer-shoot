//Hero2.cpp

//Game includes
#include "EventNuke.h"
#include "Hero2.h"
#include "Bullet.h"
#include "GameOver.h"
#include "Explosion.h"
#include "GameStatus.h"

//Engine includes
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "EventStep.h"
#include "EventView.h"




Hero2::Hero2()
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
	registerInterest(df::KEYBOARD_EVENT); //listen for keypresses
	registerInterest(df::STEP_EVENT);
	registerInterest(df::MOUSE_EVENT);

	setType("Hero");
	df::WorldManager &world_manager = df::WorldManager::getInstance();
	df::Vector p(7, world_manager.getBoundary().getVertical() / 3);
	setPosition(p);

	//move speed
	move_slowdown = 2;
	move_countdown = move_slowdown;

	//fire limits
	fire_slowdown = 15;
	fire_countdown = fire_slowdown;

	fire();
}

int Hero2::eventHandler(const df::Event *p_e)
{
	if (p_e->getType() == df::KEYBOARD_EVENT)
	{
		const df::EventKeyboard *p_keyboard_event =
			dynamic_cast <const df::EventKeyboard *> (p_e);
		kbd(p_keyboard_event);
		return 1;
	}
	else if (p_e->getType() == df::STEP_EVENT)
	{
		step();
		return 1;
	}	

	return 0;
}

void Hero2::kbd(const df::EventKeyboard *p_keyboard_event)
{

	switch (p_keyboard_event->getKey())
	{

	case df::Keyboard::UPARROW:    // up
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			move(-1);
		break;
	case df::Keyboard::DOWNARROW:    // down
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			move(+1);
		break;

	case df::Keyboard::RIGHTARROW:
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
		{
			fire();			
		}
			
		break;


	}
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
}

void Hero2::fire()
{
	// Fire Bullet straight out

	//check if the limit has been exceeded
	if (fire_countdown > 0)
		return;	
	fire_countdown = fire_slowdown;

	Bullet *p = new Bullet(getPosition());	

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
void Hero2::step()
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
Hero2::~Hero2()
{
	GameStatus::player2dies();

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