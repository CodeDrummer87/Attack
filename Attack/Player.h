#pragma once

#include "Tank.h"

class Player : public Tank
{
private:
	int totalKills;
	int currentExperience;
	int experience;
public:
	bool hasRank;
	bool preferment;
	bool isCommander;

	bool isAirSpotter;
	bool isTargetCreated;

	double xTargetPosition;
	double yTargetPosition;

	//.:: Constructors :::::::::::::::::::::
	Player();
	Player(Animation&, Animation&, double, double, int, int);

	//.:: Destructor :::::::::::::::::::::::
	virtual ~Player();

	//.:: Methods_of_class :::::::::::::::::
	void update(double);
	void nickDown(int);
	void improveTank(int);
};