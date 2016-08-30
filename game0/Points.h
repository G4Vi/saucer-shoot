#pragma once
//Points.h

//Engine includes
#include "ViewObject.h"
#include "Event.h"

extern const char* POINTS_STRING; //defined in Points.cpp

class Points : public df::ViewObject
{

public:
	Points();
	int eventHandler(const df::Event *p_e);
};