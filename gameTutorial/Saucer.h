#pragma once
//Saucer.h

//Engine includes
#include "Object.h"
#include "EventOut.h"
#include "EventCollision.h"

class Saucer : public df::Object
{
private:	
	void out();
	void moveToStart();
	void hit(const df::EventCollision *p_c);
	void nuked();
public:
	Saucer();
	~Saucer();
	int eventHandler(const df::Event *p_e);
};
