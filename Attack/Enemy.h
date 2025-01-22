#pragma once

#include "Tank.h"
#include "Player.h"

struct EvilTank
{
	bool isVillain;
	Tank *tank;
	int finishVillainTime;
};

class Enemy : public Tank
{
private:
	Animation aVehicleOutline;

public:
	bool round;

	static EvilTank evilTank;

	//.:: Constructor :::::::::::::::::::::::
	Enemy();
	Enemy(Animation&, Animation&, double, double, SoundBuffer&, int);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Enemy();

	//.:: Public_method_of_class ::::::::::::
	void destroyBrickWalls(string*);
	void destroyPlayerTanks(Tank*);

};
