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
	Color currentColor;

public:
	bool round;
	bool isInRadarCoverageArea;

	static EvilTank evilTank;

	//.:: Constructor :::::::::::::::::::::::
	Enemy();
	Enemy(Animation&, double, double, SoundBuffer&, int);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Enemy();

	//.:: Public_method_of_class ::::::::::::
	void destroyBrickWalls(string*);
	void destroyPlayerTanks(Tank*);
	void update(double);
	void applyCamouflage();

};
