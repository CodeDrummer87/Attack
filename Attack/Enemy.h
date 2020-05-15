#pragma once

#include "Tank.h"

class Enemy : public Tank
{
public:
	bool round;
	int reachDistance;
	bool isVillain;
	int finishVillainTime;

	//.:: Constructors ::::::::::::::::::::::
	Enemy();
	Enemy(Animation&, Animation&, int, int, int, int);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Enemy();

	//.:: Methods_of_class ::::::::::::::::::
	void update(double);
	void changeDir();
};