//GameStatus.cpp

#include "GameStatus.h"
#include "GameOver.h"

//engine includes
#include "WorldManager.h"

df::Object* GameStatus::player1 = NULL;
df::Object* GameStatus::player2 = NULL;

void GameStatus::init(df::Object* _player1, df::Object* _player2)
{
	player1 = _player1;
	if (_player2)
	{		
		player2 = _player2;
	}
	else
	{		
		player2 = NULL;		
	}
}

void GameStatus::player1dies()
{
	
	player1 = NULL;
	if (!player2)
		GameOver *p_go = new GameOver;
	
	/*else if (player2Alive)
	{
		df::WorldManager &world_manager = df::WorldManager::getInstance();
		world_manager.markForDelete(player2);
	}*/
	
}

void GameStatus::player2dies()
{
	player2 = NULL;
	
	if (!player1)
		GameOver *p_go = new GameOver;

	/*if (player1Alive)
	{
	df::WorldManager &world_manager = df::WorldManager::getInstance();
	world_manager.markForDelete(player1);
	}*/

}