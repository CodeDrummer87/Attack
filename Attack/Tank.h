#pragma once

#include "Entity.h"

enum Camera { NotDefined, StartGame, Commander, Target, FirstPlane, StartGameSetted };

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
	Animation aTankExplosion;
	bool isDestroyed;

	static int counter;

public:
	int number;
	int hitPoints;
	Traffic traffic;
	bool isShot;
	bool isSmoking;

	static Camera camera;

	//.:: Constructor :::::::::::::::::::::::
	Tank();
	Tank(Animation&, double, double, string, int, bool, Animation&, string, int);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Tank();

	//.:: Methods_of_class ::::::::::::::::::
	void update(double);
	void accelerate(int, double);
	bool makeSureDestroyed();

};
