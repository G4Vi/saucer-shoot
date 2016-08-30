//
// game.cpp saucer-shoot by Gavin Hayes gahayes@wpi.edu
// 

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "Color.h"
#include "Pause.h"

//Game includes
#include "Saucer.h"
#include "Hero.h"
#include "Points.h"
#include "Star.h"
#include "GameStart.h"

//prototypes
void populateWorld();
void loadResources();


int main(int argc, char *argv[])
{
	df::LogManager &log_manager = df::LogManager::getInstance();

	// Set flush of logfile during development (when done, make false).
	log_manager.setFlush(true);

	// Start up game manager.
	df::GameManager &game_manager = df::GameManager::getInstance();
	if (game_manager.startUp())
	{
		log_manager.writeLog("Error starting game manager!");
		game_manager.shutDown();
		return 0;
	}

	//Show splash screen.
	df::splash();

	//load resources
	loadResources();

	//add entities to world
	populateWorld();

	//pausing
	new df::Pause(df::Keyboard::F10);

	//start world
	game_manager.run();

	// Shut everything down.
	game_manager.shutDown(); 
}


void populateWorld(void)
{
	//spawn stars
	for (int i = 0; i<16; i++)
		new Star;

	//Spawn saucers and hero in GameStart for reusablity
	new GameStart();
}

void loadResources(void)
{
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();

	//saucer sprite.	
	resource_manager.loadSprite("sprites/saucer-spr.txt", "saucer");

	//hero sprite
	resource_manager.loadSprite("sprites/ship-spr.txt", "ship");

	//bullet sprite
	resource_manager.loadSprite("sprites/bullet-spr.txt", "bullet");

	//explosion sprite
	resource_manager.loadSprite("sprites/explosion-spr.txt", "explosion");

	//gameover sprite
	resource_manager.loadSprite("sprites/gameover-spr.txt", "gameover");

	//gamestart spire
	resource_manager.loadSprite("sprites/gamestart-spr.txt", "gamestart");

	//fire (bullet) sound
	resource_manager.loadSound("sounds/fire.wav", "fire");

	//explode sound
	resource_manager.loadSound("sounds/explode.wav", "explode");

	//nuke sound
	resource_manager.loadSound("sounds/nuke.wav", "nuke");

	//gameover sound
	resource_manager.loadSound("sounds/game-over.wav", "game over");

	//mainmenu music
	resource_manager.loadMusic("sounds/start-music.wav", "start music");
}
