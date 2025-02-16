#pragma once

#include "Enemy.h"

struct TankTowerArgs
{
	Animation& anim;
	SoundBuffer& sTurn;
	SoundBuffer& sExplosion;
	GroundVehicle* own;
};

class TankTower : public Enemy
{
private:
	GroundVehicle *own;
	CircleShape scannedZone;

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
	TankTower(TankTowerArgs&);

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
