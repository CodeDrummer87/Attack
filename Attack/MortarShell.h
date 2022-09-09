#pragma once

#include "Shell.h"
#include "TankTower.h"


struct StartPoint
{
	double totalDistance;
	double x;
	double y;
};

class MortarShell : public Shell
{
private:
	Animation aTrace;
	TankTower *own;
	StartPoint sPoint;
	double currentDistance;

	const float DEGTORAD = 0.01745329f;
	int radius;
	float factor;
	float distanceFactor;
	bool isFinishFlight;

	//.:: Methods_of_class  :::::::::::::::::
	void setExplosionVolume();
	void setShellPosition(float);
	void setTrailHeight(float);
	
public:
	bool isAreaExplosionDamaged;
	
	//.:: Constructor :::::::::::::::::::::::
	MortarShell();
	MortarShell(Animation&, Animation&, Tank*, double, double, Tank*, Animation&);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~MortarShell();

	//.:: Methods_of_class ::::::::::::::::::
	void update(double);
	double getDistanceToTarget(double, double);
	float getAccelerateFactor(double, double);
	void draw(RenderWindow&);
	void destroyTarget(Tank*);

};
