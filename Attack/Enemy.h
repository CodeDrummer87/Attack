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
	float reachedDist;
	float destinationDist;

	bool isDoubleCannon;

public:
	bool round;

	static EvilTank evilTank;

	//.:: Constructor :::::::::::::::::::::::
	Enemy();
	Enemy(Animation&, double, double, string, int, bool, Animation&, string, int, bool);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Enemy();

	//.:: Public_method_of_class ::::::::::::
	void update(double);
	void changeDir();
	void checkMapCollision(string *map);
	void updateDestinationDistance();
	void destroyBrickWalls(string*);
	void destroyPlayersTanks(Tank*);

};

