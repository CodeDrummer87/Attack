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
	Animation anim;
	bool playAnimation;
	//.:: Constructor ::::::::::::::::::::::
	Entity();	

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Entity();

	//.:: Methods_of_class ::::::::::::::::::
	virtual void setEntity(Animation&, int, int);	// animation and coordinates: x, y
	virtual void update(double);
	virtual void draw(RenderWindow&);
};

