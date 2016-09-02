#pragma once
//Hero.h

//Game includes
#include "Reticle.h"
#include "HeroBase.h"

class Hero : public HeroBase
{
	friend class SSManager;
private:
	Reticle *p_reticle;

	void fire(df::Vector target) override;

public:
	Hero();
	~Hero();
	
};