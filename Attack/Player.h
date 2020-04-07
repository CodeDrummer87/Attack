#pragma once

#include "Tank.h"

class Player : public Tank
{
private:
	int totalKills;
	int currentKillCounter;
	int experience;
public:
	//.:: Constructors :::::::::::::::::::::
	Player();
	Player(Animation&, Animation&, int, int, int, string, int);

	//.:: Destructor :::::::::::::::::::::::
	virtual ~Player();

	//.:: Methods_of_class :::::::::::::::::
	void update(double);
	void nickDown();
};

