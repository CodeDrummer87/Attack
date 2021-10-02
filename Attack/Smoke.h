#pragma once

#include "Entity.h"
#include "Tank.h"

class Smoke : public Entity
{
public:
	Tank *own;

	//.:: Constructor :::::::::::::::::::::::
	Smoke();
	Smoke(Animation&, Tank*, string);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Smoke();

	//.:: Methods_of_class ::::::::::::::::::
	void update(double);

};
