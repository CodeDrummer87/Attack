#pragma once

#include "Animation.h"

enum Status { DEAD, ALIVE, WOUNDED };

class Entity
{
protected:
	double x, y, dx, dy;

public:
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

};
