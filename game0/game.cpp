//
// game.cpp
// 

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "Color.h"

//Game includes
#include "Saucer.h"
#include "Hero.h"
#include "Points.h"
#include "Star.h"
#include "GameStart.h"

void populateWorld(void)
{   

    for (int i = 0; i<16; i++)
        new Star;

	new GameStart();
}

void loadResources(void)
{
    df::ResourceManager &resource_manager = df::ResourceManager::getInstance();

    // Load saucer sprite.	
    resource_manager.loadSprite("sprites/saucer-spr.txt", "saucer");

    //load hero sprite
    resource_manager.loadSprite("sprites/ship-spr.txt", "ship");

    //load bullet sprite
    resource_manager.loadSprite("sprites/bullet-spr.txt", "bullet");

    resource_manager.loadSprite("sprites/explosion-spr.txt", "explosion");

	resource_manager.loadSprite("sprites/gameover-spr.txt", "gameover");

	resource_manager.loadSprite("sprites/gamestart-spr.txt", "gamestart");
}

int main(int argc, char *argv[]) {

  df::LogManager &log_manager = df::LogManager::getInstance();

  // Set flush of logfile during development (when done, make false).
  log_manager.setFlush(true);

  // Start up game manager.
  df::GameManager &game_manager = df::GameManager::getInstance();
  if (game_manager.startUp())  {
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

  //start world
  game_manager.run();

  // Shut everything down.
  game_manager.shutDown();
}

