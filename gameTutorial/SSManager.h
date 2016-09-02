#pragma once
//SSManager.h

#include "Object.h"
#include "EventKeyboard.h"
#include "EventMouse.h"

//forward declarations to avoid multiple inclusion
class Hero;
class Hero2;

//Get input reading outside of hero.
class SSManager : df::Object
{
private:
	Hero* player1;
	Hero2* player2;
	static SSManager* instance;	
	SSManager(Hero* _player1, Hero2* _player2);

	void step();
	void mouse(const df::EventMouse *p_mouse_event);
	void kbd(const df::EventKeyboard *p_keyboard_event);

	void quitPressed();
	void nuke();

	int nuke_count;
	int nuke_countdown;
	int nuke_slowdown;


public:
	static SSManager* getInstance();
	static void init(Hero* _player1, Hero2* _player2 = NULL);
	void player1dies();
	void player2dies();	
	int eventHandler(const df::Event *p_e) override;
	
	~SSManager();
};