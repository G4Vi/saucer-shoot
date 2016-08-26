//
// game.cpp
// 

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"

int main(int argc, char *argv[]) {
  df::LogManager &log_manager = df::LogManager::getInstance();

  // Start up game manager.
  df::GameManager &game_manager = df::GameManager::getInstance();
  if (game_manager.startUp())  {
    log_manager.writeLog("Error starting game manager!");
    game_manager.shutDown();
    return 0;
  }

  // Set flush of logfile during development (when done, make false).
  log_manager.setFlush(true);

  // Show splash screen.
  df::splash();

  // Shut everything down.
  game_manager.shutDown();
}

