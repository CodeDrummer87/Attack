#pragma once
#include "Icon.h"


Icon::Icon()
{}

Icon::Icon(Animation icons[], Animation &b, Entity *player_, int appearanceTime)
{
	z_index = 4;
	player = player_;

	if (spawnTimer == 7)
		anim = icons[0];
	else
		anim = icons[rand() % 3 + 1];

	//.:: Testing :::::::::::::::::::::
	x = player->getCoordX(false);
	y = player->getCoordY(false) - 35;
	//:::::::::::::::::::::::::::::::::
	
	isExist = true;
	appearAnim = b;

	name = "icon";
	dir = 1;
	isPlayAnimation = true;
	level = 1;
	status = Status::ALIVE;

	spawnTimer = appearanceTime; //.:: Think about logic
}

Icon::~Icon()
{}

int Icon::spawnTimer = 7;

void Icon::update(double time)
{
	if (isExist)
	{
		if (status == Status::DEAD)
			isExist = false;
	}
}
