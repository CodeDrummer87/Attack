#pragma once

#include "Entity.h"

enum Status { DEAD, ALIVE, WOUNDED };

class Tank : public Entity
{
private:
	bool isTransition;

protected:
	static int counter;
	Animation aTankExplosion;
	bool isDestroyed;

public:
	int hitPoints;
	int level;
	Status status;
	string army;
	bool isShot;
	bool isSmoking;

	//.:: Constructor :::::::::::::::::::::::
	Tank();
	Tank(Animation&, double, double, string, int, bool, Animation&, string, int);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Tank();

	//.:: Methods_of_class ::::::::::::::::::
	void update(double);

};
