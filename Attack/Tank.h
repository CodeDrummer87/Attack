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
	bool isSmoking;

	//.:: Constructors :::::::::::::::::::::
	Tank();
	Tank(Animation&, Animation&, int, int, int, string);

	//.:: Destructor :::::::::::::::::::::::
	virtual ~Tank();

	//.:: Methods_of_class :::::::::::::::::
	void update(double);
	void accelerate(int, double);		// direction and accelerate
};