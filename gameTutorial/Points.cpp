//Points.cpp

//Game includes
#include "Points.h"

//Engine includes
#include "EventStep.h"

const char* POINTS_STRING = "Points"; //extern from Points.h

Points::Points()
{
	setLocation(df::TOP_RIGHT);
	setViewString(POINTS_STRING);
	setColor(df::YELLOW);

	registerInterest(df::STEP_EVENT);
}

int Points::eventHandler(const df::Event *p_e)
{
	// Parent handles event if score update.
	if (df::ViewObject::eventHandler(p_e))
		return 1;
	

	if (p_e->getType() == df::STEP_EVENT)
	{
		if (dynamic_cast <const df::EventStep *> (p_e)->getStepCount() % 30 == 0)
			setValue(getValue() + 1);
		return 1;
	}

	return 0;
}
	
		