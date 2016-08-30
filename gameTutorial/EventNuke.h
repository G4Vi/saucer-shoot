#pragma once
//EventNuke.h

//Engine includes
#include "Event.h"

//std includes
#include <string>


const std::string NUKE_EVENT = "nuke";

class EventNuke : public df::Event
{
public:
	EventNuke();
};