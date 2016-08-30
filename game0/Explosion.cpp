#include "Explosion.h"

#include "EventStep.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "ResourceManager.h"

Explosion::Explosion()
{
	// Dragonfly managers needed for this method.
	df::LogManager &log_manager = df::LogManager::getInstance();
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	//df::WorldManager &world_manager = df::WorldManager::getInstance();

	// Setup "saucer" sprite.
	df::Sprite *p_temp_sprite = resource_manager.getSprite("explosion");
	if (!p_temp_sprite) 
	{
		log_manager.writeLog("Explosion::Explosion(): Warning! Sprite '%s' not found",
			"explosion");
	}
	else 
	{
		setSprite(p_temp_sprite);		
	}

	// Set object type.
	setType("Explosion");
	setSolidness(df::SPECTRAL);

	registerInterest(df::STEP_EVENT);

	time_to_live = getSprite()->getFrameCount();
}
int Explosion::eventHandler(const df::Event * p_e)
{
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	return 0;
}

void Explosion::step()
{
	time_to_live--;
	if (time_to_live <= 0) {
		df::WorldManager &world_manager = df::WorldManager::getInstance();
		world_manager.markForDelete(this);
	}
}