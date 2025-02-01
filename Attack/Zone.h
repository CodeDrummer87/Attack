#pragma once

#include "Entity.h"

class Zone : public Entity
{
private:
	//.:: Methods_of_class ::::::::::::::::::
	void setPosition();

public:
	Entity* own; 
	CircleShape zone;

	//.:: Constructor :::::::::::::::::::::::
	Zone();
	Zone(Entity*, float);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Zone();

	//.:: Methods_of_class ::::::::::::::::::
	void update(double);

};
