#pragma once

#include "Entity.h"
#include "Tank.h"

class Shell : public Entity
{
private:
	float range;	// Max flight range
	float dist;		// The way done
	Animation animSpare;
	Tank *own;
public:
	//.:: Constructor ::::::::::::::::::::::
	Shell();
	Shell(Animation&, Animation&, Tank*);

	//.:: Destructor :::::::::::::::::::::::
	virtual ~Shell();

	//.:: Methods_of_class :::::::::::::::::
	void update(double);
};