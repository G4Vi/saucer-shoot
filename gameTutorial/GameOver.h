#pragma once
//GameOver.h

//Engine includes
#include "ViewObject.h"

class GameOver : public df::ViewObject 
{
private:
	int time_to_live;
	void step();

public:
	GameOver();
	~GameOver();
	void draw() override;
	int eventHandler(const df::Event *p_e);

};