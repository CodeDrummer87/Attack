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
public:
	bool round;

	static EvilTank evilTank;

	//.:: Constructor :::::::::::::::::::::::
	Enemy();
	Enemy(Animation&, double, double, string, int, bool, SoundBuffer&, int, string, int);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Enemy();

	//.:: Public_method_of_class ::::::::::::
	void destroyBrickWalls(string*);
	void destroyPlayerTanks(Tank*);

};
