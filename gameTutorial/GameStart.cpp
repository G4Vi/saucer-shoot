//GameStart.cpp

//Game includes
#include "Saucer.h"
#include "Hero.h"
#include "Hero2.h"
#include "Points.h"
#include "GameStart.h"
#include "SSManager.h"

//Engine includes
#include "LogManager.h"
#include "ResourceManager.h"
#include "GameManager.h"

GameStart::GameStart()
{
	// Dragonfly managers needed for this method.
	df::LogManager &log_manager = df::LogManager::getInstance();
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	//df::WorldManager &world_manager = df::WorldManager::getInstance();

	df::Sprite *p_temp_sprite = resource_manager.getSprite("gamestart");
	if (!p_temp_sprite)
	{
		log_manager.writeLog("GameStart::GameStart(): Warning! Sprite '%s' not found",
			"gamestart");
	}
	else
	{
		setSprite(p_temp_sprite);
		setSpriteSlowdown(15);
	}
	
	setType("GameStart");
	setLocation(df::CENTER_CENTER);
   
	registerInterest(df::KEYBOARD_EVENT);

	p_music = df::ResourceManager::getInstance().getMusic("start music");

	if (!p_music)
	{
		log_manager.writeLog("GameStart::GameStart(): Warning! Music '%s' not found",
			"start music");
	}
	else
	{
		playMusic();
	}
	

		
	

}

void GameStart::kbd(const df::EventKeyboard *p_keyboard_event)
{
	df::GameManager &game_manager = df::GameManager::getInstance();

	switch (p_keyboard_event->getKey())
	{
	case df::Keyboard::P: 			// play
		start();
		break;
	case df::Keyboard::C:           //C for coop
		start(true);
		break;
	case df::Keyboard::Q:			// quit
		game_manager.setGameOver();
		break;
	default:
		break;

	}
}

int GameStart::eventHandler(const df::Event *p_e)
{
	if (p_e->getType() == df::KEYBOARD_EVENT)
	{
		const df::EventKeyboard *p_keyboard_event =
			dynamic_cast <const df::EventKeyboard *> (p_e);
		kbd(p_keyboard_event);
		return 1;
	}

	return 0;
}

void GameStart::start(bool coop)
{
	

	//new Hero;

	if(coop)
	{
		// Spawn some saucers to shoot.
		for (int i = 0; i<32; i++)
			new Saucer;
		SSManager::init(new Hero, new Hero2);
	}
	else
	{
		for (int i = 0; i<16; i++)
			new Saucer;
		SSManager::init(new Hero);
	}	

	new Points;

	setActive(false); //disable for now
	p_music->pause();
}

void GameStart::draw()
{
	df::Object::draw();
}

void GameStart::playMusic()
{
	p_music->play();
}