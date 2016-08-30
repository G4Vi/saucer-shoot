#include "GameStart.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "GameManager.h"

#include "Saucer.h"
#include "Hero.h"
#include "Points.h"

GameStart::GameStart()
{
	// Dragonfly managers needed for this method.
	df::LogManager &log_manager = df::LogManager::getInstance();
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	//df::WorldManager &world_manager = df::WorldManager::getInstance();

	df::Sprite *p_temp_sprite = resource_manager.getSprite("gamestart");
	if (!p_temp_sprite) {
		log_manager.writeLog("GameStart::GameStart(): Warning! Sprite '%s' not found",
			"gamestart");
	}
	else
	{
		setSprite(p_temp_sprite);		
		setSpriteSlowdown(15);
		setType("GameStart");
		

		setLocation(df::CENTER_CENTER);

		registerInterest(df::KEYBOARD_EVENT);
	}

}

void GameStart::kbd(const df::EventKeyboard *p_keyboard_event)
{
	df::GameManager &game_manager = df::GameManager::getInstance();

	switch (p_keyboard_event->getKey()) {
	case df::Keyboard::P: 			// play
		start();
		break;
	case df::Keyboard::Q:			// quit
		game_manager.setGameOver();
		break;
	default:
		break;
	}
}

int GameStart::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::KEYBOARD_EVENT)
	{
		const df::EventKeyboard *p_keyboard_event =
			dynamic_cast <const df::EventKeyboard *> (p_e);
		kbd(p_keyboard_event);
		return 1;
	}

	return 0;
}

void GameStart::start()
{
	// Spawn some saucers to shoot.
	for (int i = 0; i<16; i++)
		new Saucer;

	new Hero;

	new Points;
	df::ViewObject *p_vo = new df::ViewObject;
	p_vo->setLocation(df::TOP_LEFT);
	p_vo->setViewString("Nukes");
	p_vo->setValue(1);
	p_vo->setColor(df::YELLOW);

	setActive(false); //disable for now
}

void GameStart::draw()
{
	df::Object::draw();
}