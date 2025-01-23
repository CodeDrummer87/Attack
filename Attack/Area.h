#pragma once

#include "Entity.h"

class Area : public Entity
{
private:
	//.:: Methods_of_class ::::::::::::::::::
	void setPosition();

public:
	Entity* own; 
	CircleShape area;

	//.:: Constructor :::::::::::::::::::::::
	Area();
	Area(Entity*, float);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Area();

	//.:: Methods_of_class ::::::::::::::::::
	void update(double);

};
