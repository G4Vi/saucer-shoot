#include "GameOver.h"
#include "GameStart.h"


#include "ResourceManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "GameManager.h"

#include "EventStep.h"

GameOver::GameOver()
{
	// Dragonfly managers needed for this method.
	df::LogManager &log_manager = df::LogManager::getInstance();
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	//df::WorldManager &world_manager = df::WorldManager::getInstance();
	
	df::Sprite *p_temp_sprite = resource_manager.getSprite("gameover");
	if (!p_temp_sprite) {
		log_manager.writeLog("GameOver::GameOver(): Warning! Sprite '%s' not found",
			"gameover");
	}
	else 
	{
		setSprite(p_temp_sprite);
		setTransparency('#');
		setSpriteSlowdown(15);
		setType("GameOver");
		time_to_live = p_temp_sprite->getFrameCount() * 15;

		setLocation(df::CENTER_CENTER);
		
		registerInterest(df::STEP_EVENT);

		df::Sound *p_sound = df::ResourceManager::getInstance().getSound("game over");
		p_sound->play();
	}

}

int GameOver::eventHandler(const df::Event *p_e) {	
	if (p_e->getType() == df::STEP_EVENT)
	{
		step();
		return 1;
	}

	return 0;
}

void GameOver::step() {
	time_to_live--;
	if (time_to_live <= 0) {
		df::WorldManager &world_manager = df::WorldManager::getInstance();
		world_manager.markForDelete(this);
	}
}

GameOver::~GameOver() 
{
	/*df::GameManager &game_manager = df::GameManager::getInstance();
	game_manager.setGameOver();*/

	df::WorldManager &world_manager = df::WorldManager::getInstance();

	// Remove Saucers and ViewObjects, re-activate GameStart.
	df::ObjectList object_list = world_manager.getAllObjects(true);
	df::ObjectListIterator i(&object_list);
	for (i.first(); !i.isDone(); i.next()) {
		df::Object *p_o = i.currentObject();
		if (p_o->getType() == "Saucer" || p_o->getType() == "ViewObject")
			world_manager.markForDelete(p_o);
		if (p_o->getType() == "GameStart")
		{
			p_o->setActive(true);
			dynamic_cast <GameStart *> (p_o)->playMusic(); // Resume start music.
		}
	}
	
}

void GameOver::draw()
{
	df::Object::draw();
}