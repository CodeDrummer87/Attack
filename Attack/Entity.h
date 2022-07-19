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
	  0 - puddle, zone
	  1 - enemy's tank, player's tank
	  2 - smoke
	  3 - boss tank
	  4 - smoke for the boss
	  5 - air objects below the aircraft (for example a bomb), target
	  6 - aircraft
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

};
