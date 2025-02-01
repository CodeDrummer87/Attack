#include "DestructionZone.h"

DestructionZone::DestructionZone()
{}

DestructionZone::DestructionZone(Entity *own_, float radius)
	: Zone(own_, radius)
{
	name = "destructionZone";
	isTerrainDestroyed = false;
	number = 0;
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
