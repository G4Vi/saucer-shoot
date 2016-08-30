#pragma once
//GameStart.h

//Engine includes
#include "ViewObject.h"
#include "EventKeyboard.h"
#include "Music.h"

class GameStart : public df::ViewObject
{

private:
	void start();
	void kbd(const df::EventKeyboard *p_keyboard_event);

	df::Music *p_music;
public:
	GameStart();
	int eventHandler(const df::Event *p_e);
	void draw();
	void playMusic();
};

