#pragma once

#include "Entity.h"

class Shell : public Entity
{
private:
	float range;	// Max flight range
	float dist;		// The way done
	Animation animSpare;
public:
	//.:: Constructor ::::::::::::::::::::::
	Shell();
	Shell(Animation&, Animation&, int, int, int, string);

	//.:: Destructor :::::::::::::::::::::::
	virtual ~Shell();

	//.:: Methods_of_class :::::::::::::::::
	void update(double);
};