#include "DestructionZone.h"

DestructionZone::DestructionZone()
{}

DestructionZone::DestructionZone(Entity *own_, float radius)
	: Area(own_, radius)
{
	name = "destructionZone";
	isTerrainDestroyed = false;
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
