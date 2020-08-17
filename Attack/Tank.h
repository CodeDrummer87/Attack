#pragma once

#include "Entity.h"

using namespace sf;

class Tank : public Entity
{
private:
	Animation aTankExplosion;
	bool destroyed;
	bool transition;

protected:
	int mapWidth;
	int mapHeight;

public:
	bool isShot;
	bool isSmoking;
	bool isTowed;
	bool isDrowned;
	bool drowning;
	static bool cameraIsNotFree;

	//.:: Constructors :::::::::::::::::::::
	Tank();
	Tank(Animation&, Animation&, int, int, int, int, const int, const int);

	//.:: Destructor :::::::::::::::::::::::
	virtual ~Tank();

	//.:: Methods_of_class :::::::::::::::::
	void update(double);
	void accelerate(int, double);		// direction and accelerate
	bool makeSureDestroyed();
};