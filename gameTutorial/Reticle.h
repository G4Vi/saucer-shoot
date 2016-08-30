#pragma once
//Recticle.h

//Engine includes
#include "Object.h"

const char RETICLE_CHAR = '+';

class Reticle : public df::Object
{

public:
	Reticle();
	void draw(void);
	int eventHandler(const df::Event *p_e);
};