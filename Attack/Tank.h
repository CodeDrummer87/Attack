#pragma once

#include "Entity.h"

enum Camera { NotDefined, StartGame, Commander, MalevolentTank, Target, FirstPlane, StartGameSetted };

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

	float speedBonus;	//.:: Achievement "Cleaner": Speed boost bonus
	short destValue;

protected:
	Animation aTankExplosion;
	bool isDestroyed;

	int drownedTanks;
	Tank *pusher;

	static int counter;

public:
	int number;
	int hitPoints;
	Traffic traffic;
	bool isShot;
	bool isSmoking;

	bool isDrowned;
	bool drowning;

	bool isSpeedBonusUp;

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
	void checkTanksCollision(Tank*);
	void shoveOffTankCarcass(Tank*);
	void sinkTheTankCarcass(string*);
	bool makeSureTankCollision(Tank*);

};
