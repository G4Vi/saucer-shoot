#pragma once
#include "ViewObject.h"
#include "EventKeyboard.h"

class GameStart : public df::ViewObject {

private:
	void start();
	void kbd(const df::EventKeyboard *p_keyboard_event);
public:
	GameStart();
	int eventHandler(const df::Event *p_e);
	void draw();
};

