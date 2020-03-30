#pragma once

#include <SFML\Graphics.hpp>
#include "Animation.h"

using namespace sf;

class Entity
{
protected:
	double x, y, dx, dy;		// coordinates: x, y; acceleration x and y;
public:
	int dir;
	Animation anim;
	bool playAnimation;
	bool isExist;
	//.:: Constructors ::::::::::::::::::::::
	Entity();
	Entity(Animation&, int, int, int);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Entity();

	//.:: Methods_of_class ::::::::::::::::::
	virtual void setEntity(Animation&, int, int);	// animation and coordinates: x, y
	virtual void update(double);
	double getCoordX(bool);
	double getCoordY(bool);
	void draw(RenderWindow&);
};

