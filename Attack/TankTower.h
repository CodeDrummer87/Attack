#pragma once

#include "Enemy.h"

class TankTower : public Enemy
{
private:
	GroundVehicle *own;

public:
	GroundVehicle *currentTarget;
	bool isTargetSearch;

	bool roundFirst;
	bool roundSecond;
	bool isFirstShot;
	bool isSecondShot;

	bool isMortarShootTime;
	int mortarShootTime;

	//.:: Constructor :::::::::::::::::::::::
	TankTower();
	TankTower(Animation&, double, double, int, SoundBuffer&, SoundBuffer&, int, GroundVehicle*);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~TankTower();

	//.:: Methods_of_class ::::::::::::::::::
	void update(double);
	void detectTarget(vector<Player*>&, int);
	void getRotationDirection(int&, int&);
	void destroyPlayerWithCannons();
	void setNextAimingTime(int);
	Tank* getTargetForMortar(vector<Player*>);
	int takeAim(GroundVehicle*);

};
