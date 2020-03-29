#pragma once

#include "Entity.h"

class Shell : public Entity
{
private:
	float range;	// Max flight range
	float dist;		// The way done
public:
	//.:: Constructor ::::::::::::::::::::::
	Shell();
	Shell(Animation&, int, int, int);

	//.:: Destructor :::::::::::::::::::::::
	virtual ~Shell();

	//.:: Methods_of_class :::::::::::::::::
	void update(double);
};