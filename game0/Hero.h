#pragma once
#include "Object.h"
#include "EventKeyboard.h"
#include "EventMouse.h"

#include "Reticle.h"
class Hero : public df::Object {

private:
	void kbd(const df::EventKeyboard *p_keyboard_event);
	void mouse(const df::EventMouse *p_mouse_event);
	void move(int dy);
	void fire(df::Vector target);	
	void nuke();
	void step();

	int move_slowdown;
	int move_countdown;

	int fire_slowdown;
	int fire_countdown;	

	Reticle *p_reticle;

	int nuke_count;

public:
	Hero();
	~Hero();
	int eventHandler(const df::Event *p_e);
};