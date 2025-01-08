#pragma once

#include "Animation.h"

enum Status { DEAD, ALIVE, WOUNDED };

class Entity
{
protected:
	double x, y, dx, dy;

public:
	/*
	  z_index:
	  0 - map default
	  1 - puddle, zone, mines
	  2 - all land vehicles
	  3 - smoke
	  4 - boss tank
	  5 - smoke for the boss
	  6 - air objects under the aircraft (for example a bomb), target
	  7 - aircraft
	*/
	short z_index;

	int number;
	int level;
	string name;
	string army;
	int dir;
	Status status;

	Animation anim;
	bool isPlayAnimation;
	bool isExist;

	//.:: Constructor :::::::::::::::::::::::
	Entity();
	Entity(Animation&, double, double, string, int, bool); //.:: anim, x, y, name, dir, isPlayAnimation

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Entity();

	//.:: Methods_of_class  :::::::::::::::::
	virtual void update(double) = 0;
	virtual void draw(RenderWindow&);

	double getCoordX(bool);
	double getCoordY(bool);
	void setCoordX(double);
	void setCoordY(double);
	int getCounterDirection(int);
	void resetDegrees(int&);
	bool isUndeletable();
	bool isAnyGroundVehicle();
	bool isGroundVehicle();

};
