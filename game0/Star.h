#pragma once
//Star.h

//Engine includes
#include "Object.h"

const char STAR_CHAR = '.';

class Star : public df::Object
{

private:
	void out();

public:
	Star();
	void draw(void);
	int eventHandler(const df::Event *p_e);
};
