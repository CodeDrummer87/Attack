#pragma once

#include "Enemy.h"

struct BossArgs
{
	Animation &anim;
	SoundBuffer& sExplosion;
	int mapIndex;
	int numberOfPlayers;	
};

class Boss : public Enemy
{
private:
	int mapIndex;

public:
	bool isOilSpillage;
	int nextOilSpillageTime;

	bool isAiming;
	int aimingTime;

	bool wasDustClap;

	//.:: Constructor :::::::::::::::::::::::
	Boss();
	Boss(BossArgs&);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Boss();

	//.:: Methods_of_class ::::::::::::::::::
	void update(double);
	void checkMapCollision(string*);

};
