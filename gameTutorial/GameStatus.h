#pragma once
//GameStatus.h

#include "Object.h"

class GameStatus
{
private:
	static df::Object* player1;
	static df::Object* player2;


public:
	static void init(df::Object* _player1, df::Object* _player2 = NULL);
	static void player1dies();
	static void player2dies();
	
};