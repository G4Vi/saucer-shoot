//SSManager.cpp

#include "SSManager.h"
#include "GameOver.h"
#include "Hero.h"
#include "Hero2.h"
#include "EventNuke.h"

//engine includes
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventView.h"
#include "EventStep.h"


SSManager* SSManager::instance = NULL;

void SSManager::init(Hero* _player1, Hero2* _player2)
{
	if (!instance)
	{
		new SSManager(_player1, _player2);
	}
	//fail silently if one exists rather than allowing 2 to exist
}

SSManager::SSManager(Hero* _player1, Hero2* _player2)
{
	player1 = _player1;
	if (_player2)
	{
		player2 = _player2;
		nuke_count = 2;  //2 because 2 players
	}
	else
	{
		player2 = NULL;
		nuke_count = 1;
	}

	df::ViewObject *p_vo = new df::ViewObject;
	p_vo->setLocation(df::TOP_LEFT);
	p_vo->setViewString("Nukes");
	p_vo->setValue(nuke_count);
	p_vo->setColor(df::YELLOW);

	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::STEP_EVENT);
	registerInterest(df::MOUSE_EVENT);

	instance = this;

	//nuke slowdown
	nuke_slowdown = 15;
	nuke_countdown = nuke_slowdown;
}
SSManager* SSManager::getInstance()
{
	if (!instance)
	{
		return NULL; //no instance exists, must be inited so return null
	}
	else
		return instance;
}

SSManager::~SSManager()
{
	instance = NULL;
}
void SSManager::player1dies()
{
	
	player1 = NULL;
	if (!player2)
		GameOver *p_go = new GameOver;	
}

void SSManager::player2dies()
{
	player2 = NULL;
	
	if (!player1)
		GameOver *p_go = new GameOver;

}

int SSManager::eventHandler(const df::Event *p_e)
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
	else if (p_e->getType() == df::MOUSE_EVENT)
	{
		const df::EventMouse *p_mouse_event =
			dynamic_cast <const df::EventMouse *> (p_e);
		mouse(p_mouse_event);
		return 1;
	}
	return 0;
}

void SSManager::step()
{
	//Avoid using 2 nukes at once
	nuke_countdown--;
	if (nuke_countdown < 0)
		nuke_countdown = 0;
}

void SSManager::mouse(const df::EventMouse *p_mouse_event)
{
	if (player1)
	{
		if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
			(p_mouse_event->getMouseButton() == df::Mouse::LEFT))
			player1->fire(p_mouse_event->getMousePosition());
	}
}


void SSManager::kbd(const df::EventKeyboard *p_keyboard_event)
{
	df::Keyboard::Key aKey = p_keyboard_event->getKey();
	
	switch (aKey)
	{
	//commands relevant to both players
	case df::Keyboard::Q:    // quit
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
			SSManager::getInstance()->quitPressed();
		
		return;
		break;

	case df::Keyboard::SPACE:
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			nuke();

		return;
		break;
	default:
		if (player1)
		{
			//player1 controls
			switch (aKey)
			{
			case df::Keyboard::UPARROW:    // Hero up
				if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
					player1->move(-1);

				return;
				break;
			case df::Keyboard::DOWNARROW:    // down
				if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
					player1->move(+1);

				return;
				break;
			}
		}

		if(player2)
		{
			//player2 controls
			switch (aKey)
			{
			case df::Keyboard::W:    // up
				if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
					player2->move(-1);

				return;
				break;
			case df::Keyboard::S:    // down
				if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
					player2->move(+1);

				return;
				break;

			case df::Keyboard::D:
				if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
				{
					player2->fire();
				}

				return;
				break;
			
			}
		}
	}
	


}

void SSManager::quitPressed()
{
	df::WorldManager &world_manager = df::WorldManager::getInstance();

	//if player1 exists, kill him as game is over as quit was pressed
	if (player1)
	{		
		world_manager.markForDelete((Object*)player1);
	}

	//if player2 exists, kill him as game is over as quit was pressed
	if (player2)
	{
		world_manager.markForDelete((Object*)player2);	
	}
	
	//SSManager dies in GameOver
	
}

void SSManager::nuke()
{
	//check if the limits has been exceeded
	if (nuke_countdown > 0)
		return;
	nuke_countdown = nuke_slowdown;

	if (!nuke_count)
		return;
	nuke_count--;

	df::WorldManager &world_manager = df::WorldManager::getInstance();
	EventNuke nuke;
	world_manager.onEvent(&nuke);

	df::EventView ev("Nukes", -1, true);
	world_manager.onEvent(&ev);

	df::Sound *p_sound = df::ResourceManager::getInstance().getSound("nuke");
	if (!p_sound)
	{
		df::LogManager &log_manager = df::LogManager::getInstance();
		log_manager.writeLog("Hero::nuke(): Warning! Sound '%s' not found",
			"nuke");
	}
	else
	{
		p_sound->play();
	}

}
