#include "Star.h"

#include "GraphicsManager.h"
#include "WorldManager.h"
#include "EventOut.h"

Star::Star()
{
	setType("Star");
	setSolidness(df::SPECTRAL);
	setVelocity(df::Vector((float)-1.0 / (rand() % 10 + 1), 0));
	setAltitude(0);

	df::WorldManager &world_manager = df::WorldManager::getInstance();
	df::Vector p((float)(rand() % (int)world_manager.getBoundary().getHorizontal()),
		(float)(rand() % (int)world_manager.getBoundary().getVertical()));
	setPosition(p);
}

void Star::draw() {
	df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();
	graphics_manager.drawCh(getPosition(), STAR_CHAR, df::WHITE);
}

void Star::out() {
	df::WorldManager &world_manager = df::WorldManager::getInstance();
	df::Vector p((float)(world_manager.getBoundary().getHorizontal() + rand() % 20),
		(float)(rand() % (int)world_manager.getBoundary().getVertical()));
	setPosition(p);
	setVelocity(df::Vector(-1.0 / (rand() % 10 + 1), 0));
}

int Star::eventHandler(const df::Event * p_e)
{
	if (p_e->getType() == df::OUT_EVENT)
	{
		out();
		return 1;
	}
	return 0;
}
