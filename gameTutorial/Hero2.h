#pragma once
//Hero2.h
#include "HeroBase.h"

class Hero2 : public HeroBase
{
	friend class SSManager;

private:
	void fire() override;
	
	

public:
	Hero2();
	~Hero2();	
};