#pragma once

#include "Entity.h"

struct Ban
{
	bool dir;	//.:: Direction open / close
	int barId;	//.:: Barrier ID (if Direction is close)
};

struct Traffic
{
	Ban up;
	Ban right;
	Ban down;
	Ban left;
};

class Tank : public Entity
{
private:
	bool isTransition;
	double toUp, toRight, toDown, toLeft;

protected:
	static int counter;
	Animation aTankExplosion;
	bool isDestroyed;

public:
	int number;
	int hitPoints;
	Traffic traffic;
	bool isShot;
	bool isSmoking;

	//.:: Constructor :::::::::::::::::::::::
	Tank();
	Tank(Animation&, double, double, string, int, bool, Animation&, string, int);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Tank();

	//.:: Methods_of_class ::::::::::::::::::
	void update(double);
	void accelerate(int, double);

};
