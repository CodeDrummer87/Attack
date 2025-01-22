#include "DestructionZone.h"

DestructionZone::DestructionZone()
{}

DestructionZone::DestructionZone(double X, double Y, float radius, Entity *own_)
	: Area(own_, radius)
{
	name = "destructionZone";
	isTerrainDestroyed = false;

	x = X;
	y = Y;
}

short DestructionZone::victims = 0;
int DestructionZone::totalExperience = 0;

DestructionZone::~DestructionZone()
{}

void DestructionZone::update(double time)
{
	if (status == WOUNDED)
	{
		totalExperience = 0;
		victims = 0;

		isExist = false;
	}

	if (own->status == WOUNDED && !own-isExist)
		status = WOUNDED;
}
