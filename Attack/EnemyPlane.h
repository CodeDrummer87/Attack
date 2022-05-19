#pragma once

#include "Air.h"
#include "Player.h"

class EnemyPlane : public Air
{
private:
	int mapHeight;
	double dropPoint;

	Animation aEssential;
	Animation aTrace;
	Animation aJetFlame;

public:
	BombStatus bombStatus;
	
	static Player *target;

	//.:: Constructor ::::::::::::::::::::::
	EnemyPlane();
	EnemyPlane(Animation&, Animation&, Animation&, double, double, string, double, int);

	//.:: Destructor :::::::::::::::::::::::
	virtual ~EnemyPlane();

	//.:: Methods_of_class :::::::::::::::::
	void update(double);
	void draw(RenderWindow&);

};

