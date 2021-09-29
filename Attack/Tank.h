#pragma once

#include "Entity.h"

class Tank : public Entity
{
protected:
	static int counter;
	Animation aTankExplosion;
	bool destroyed;

public:
	string army;
	bool isShot;
	bool isSmoking;

	//.:: Constructor :::::::::::::::::::::::
	Tank();
	Tank(Animation&, double, double, string, int, bool, Animation&, string);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Tank();

	//.:: Methods_of_class  :::::::::::::::::
};
