#pragma once

#include "Entity.h"

using namespace sf;

class Tank : public Entity
{
private:
	Animation aTankExplosion;
	bool destroyed;
	bool transition;
public:
	bool isShot;
	bool isSmoking;

	//.:: Constructors :::::::::::::::::::::
	Tank();
	Tank(Animation&, Animation&, int, int, int, string, int);

	//.:: Destructor :::::::::::::::::::::::
	virtual ~Tank();

	//.:: Methods_of_class :::::::::::::::::
	void update(double);
	void accelerate(int, double);		// direction and accelerate
};