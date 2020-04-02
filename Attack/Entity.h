#pragma once

#include <SFML\Graphics.hpp>
#include "Animation.h"

using namespace sf;

enum Status { DEAD, ALIVE, WOUNDED };

class Entity
{
protected:
	static int counter;
	double x, y, dx, dy;		// coordinates: x, y; acceleration x and y;
public:
	int tokenId;
	string name;
	int dir;
	Animation anim;
	bool playAnimation;
	bool isExist;
	Status status;
	//.:: Constructors ::::::::::::::::::::::
	Entity();
	Entity(Animation&, int, int);		//.:: For Smoke
	Entity(Animation&, int, int, int);	//.:: For Explosion

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Entity();

	//.:: Methods_of_class ::::::::::::::::::
	virtual void update(double);
	virtual void collideEntities(Entity*);
	double getCoordX(bool);
	double getCoordY(bool);
	void draw(RenderWindow&);
};

