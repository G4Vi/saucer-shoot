#pragma once
//Hero2.h

//Engine includes
#include "Object.h"
#include "EventKeyboard.h"
#include "EventMouse.h"


class Hero2 : public df::Object
{

private:
	void kbd(const df::EventKeyboard *p_keyboard_event);	
	void move(int dy);
	void fire();	
	void step();

	int move_slowdown;
	int move_countdown;

	int fire_slowdown;
	int fire_countdown;
	

public:
	Hero2();
	~Hero2();
	int eventHandler(const df::Event *p_e);
};