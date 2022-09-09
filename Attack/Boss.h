#pragma once

#include "Enemy.h"

struct BossArgs
{
	Animation &anim;
	double x;
	double y;
	int dir;
	bool isPlayAnimation;
	int level;
	int numberOfPlayers;

	SoundBuffer &sExplosion;
	int expFrameCount;
};

class Boss : public Enemy
{
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
