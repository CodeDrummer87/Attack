#pragma once

#include "Enemy.h"
#include "Boss.h"

struct TankTowerArgs
{
	Animation& anim;
	SoundBuffer& sTurn;
	SoundBuffer& sExplosion;
	Boss* own;
};

class TankTower : public Enemy
{
private:
	CircleShape scannedZone;

public:
	Boss* own;
	GroundVehicle *currentTarget;
	bool isTargetSearch;

	bool roundFirst;
	bool roundSecond;
	bool isFirstShot;
	bool isSecondShot;

	bool isMortarShotTime;
	bool isRampageAccumulating;

	int actionTime;

	//.:: Constructor :::::::::::::::::::::::
	TankTower();
	TankTower(TankTowerArgs&);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~TankTower();

	//.:: Methods_of_class ::::::::::::::::::
	void update(double);
	void detectTarget(Player*,int,  int);
	void getRotationDirection(int&, int&);
	void destroyPlayerByCannon();
	void destroyPlayerByCannons();
	void setNextAimingTime(int, bool&);
	Tank* getTargetForMortar(vector<Player*>);
	int takeAim(GroundVehicle*);
	void checkMortarShotTime(int);
	void checkRampageAccumulation(int);
	void chooseBehavior(int, int);

};
