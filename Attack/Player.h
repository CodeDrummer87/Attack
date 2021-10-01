#pragma once

#include "Tank.h"

class Player : public Tank
{
private:
	int totalKills;
	int currentExperience;
	int requiredExperience;

public:
	bool hasRank;
	bool preferment;
	bool isCommander;

	//.:: Constructor ::::::::::::::::::::::
	Player();
	Player(Animation&, double, double, string, int, bool, Animation&, string, int);

	//.:: Destructor :::::::::::::::::::::::
	virtual ~Player();

	//.:: Methods_of_class :::::::::::::::::
	void update(double);
	void setStartPosition(double, double);

};
