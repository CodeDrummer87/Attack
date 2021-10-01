#pragma once

#include "Animation.h"

class Entity
{
protected:
	double x, y, dx, dy;

public:
	string name;
	int dir;	

	Animation anim;
	bool isPlayAnimation;
	bool isExist;

	//.:: Constructor :::::::::::::::::::::::
	Entity();
	Entity(Animation&, double, double, string, int, bool); //.:: anim, x, y, name, dir, isPlayAnimation

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Entity();

	//.:: Methods_of_class  :::::::::::::::::
	virtual void update(double);
	virtual void draw(RenderWindow&);

};
