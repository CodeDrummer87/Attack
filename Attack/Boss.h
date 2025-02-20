#pragma once

#include "Enemy.h"

struct BossArgs
{
	Animation& anim;
	SoundBuffer& sExplosion;
	int mapIndex;
	int numberOfPlayers;
	Sound* activitySound;
};

class Boss : public Enemy
{
private:
	float red;
	float greenAndBlue;
	Sound* activitySound;

	//.:: Methods_of_class ::::::::::::::::::
	void setSpriteColor(float, float, float);

public:
	bool isOilSpillage;
	int nextOilSpillageTime;
	bool wasHalfDestroyed;

	int timeToAct;
	bool isActing;
	bool isAnimationRun;

	//.:: Constructor :::::::::::::::::::::::
	Boss();
	Boss(BossArgs&);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Boss();

	//.:: Methods_of_class ::::::::::::::::::
	void update(double);
	void checkMapCollision(string*);
	void slowDownSpeed();
	void getAngry();
	void coolDown();
	bool isGetAngry();
	bool isReadyToUseAbility();

};
