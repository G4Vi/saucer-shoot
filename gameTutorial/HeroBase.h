#pragma once
//HeroBase.h

//Engine includes
#include "Object.h"

//For shared functionality between Hero objects
class HeroBase : public df::Object
{
	friend class SSManager;
private:
	void move(int dy);
	virtual void fire(df::Vector target){};
	virtual void fire(){};
	void step();

private:
	int move_slowdown;
	int move_countdown;

protected:
	int fire_slowdown;
	int fire_countdown;

	HeroBase();
	~HeroBase();

public:
	int eventHandler(const df::Event *p_e);
};