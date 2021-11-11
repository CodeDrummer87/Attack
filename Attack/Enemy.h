#pragma once

#include "Tank.h"

class Enemy : public Tank
{
private:
	bool isDoubleCannon;

public:
	static bool isVillain;
	static int finishVillainTime;

	//.:: Constructor :::::::::::::::::::::::
	Enemy();
	Enemy(Animation&, double, double, string, int, bool, Animation&, string, int, bool);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Enemy();

	//.:: Method_of_class :::::::::::::::::::
	void update(double);
	void changeDir();
	void checkMapCollision(string *map);

};

