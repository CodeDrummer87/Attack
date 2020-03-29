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

	//.:: Destructor :::::::::::::::::::::::
	virtual ~Shell();
};