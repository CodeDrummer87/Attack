#pragma once

#include "Area.h"

class DestructionZone : public Area
{
public:
	bool isTerrainDestroyed;

	static short victims;
	static int totalExperience;


	//.:: Constructor ::::::::::::::::::::::
	DestructionZone();
	DestructionZone(Entity*, float);

	//.:: Destructor :::::::::::::::::::::::
	virtual ~DestructionZone();

	//.:: Methods_of_class :::::::::::::::::
	void update(double);

};
