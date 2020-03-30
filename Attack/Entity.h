#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include "Animation.h"

using namespace std;
using namespace sf;

class Entity
{
protected:
	double x, y, dx, dy;		// coordinates: x, y; acceleration x and y;
public:
	string name;
	int dir;
	Animation anim;
	bool playAnimation;
	bool isExist;
	//.:: Constructor ::::::::::::::::::::::
	Entity();	

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Entity();

	//.:: Methods_of_class ::::::::::::::::::
	virtual void setEntity(Animation&, int, int);	// animation and coordinates: x, y
	virtual void update(double);
	double getCoordX(bool);
	double getCoordY(bool);
	void draw(RenderWindow&);
};

