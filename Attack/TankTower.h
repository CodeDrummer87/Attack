#pragma once

#include "Enemy.h"

class TankTower : public Enemy
{
private:
	GroundVehicle *own;

	bool isActive;
	GroundVehicle *currentTarget;

	//.:: Methods_of_class ::::::::::::::::::
	int takeAim(GroundVehicle*);

public:
	bool isTargetSearch;

	bool roundFirst;
	bool roundSecond;
	bool isFirstShot;
	bool isSecondShot;

	//.:: Constructor :::::::::::::::::::::::
	TankTower();
	TankTower(Animation&, double, double, int, SoundBuffer&, SoundBuffer&, int, GroundVehicle*);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~TankTower();

	//.:: Methods_of_class ::::::::::::::::::
	void update(double);
	void detectTarget(vector<Player*>&);
	void getRotationDirection(int&, int&);
	void destroyPlayerWithCannons();

	Color getCurrentColor()
	{
		return currentTarget->number == 1 ? Color::Red : currentTarget->number == 2 ? Color::Yellow : currentTarget->number == 3 ?
			Color::Magenta : currentTarget->number == 4 ? Color::Cyan : Color::Green;
	}

};
