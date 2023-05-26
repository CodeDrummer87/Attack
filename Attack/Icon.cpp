#pragma once
#include "Icon.h"


Icon::Icon()
{}

Icon::Icon(IconAnim icons[], Animation &b, Entity *player_, int appearanceTime)
{
	z_index = 4;
	player = player_;

	srand(std::time(NULL));

	int index;
	if (isFirstIcon)
	{
		index = 0;
		isFirstIcon = false;
	}
	else
		index = rand() % (sizeof(icons) - 1) + 1;

	anim = icons[index].anim;
	iconType = icons[index].iconType;

	//.:: Testing :::::::::::::::::::::
	x = player->getCoordX(false);
	y = player->getCoordY(false) - 80;
	//:::::::::::::::::::::::::::::::::
	
	isExist = true;
	appearAnim = b;

	name = "icon";
	dir = 1;
	isPlayAnimation = true;
	level = 1;
	status = Status::ALIVE;

	spawnTimer = appearanceTime; //.:: Think about logic of limit
}

Icon::~Icon()
{}

int Icon::spawnTimer = 0;
bool Icon::isFirstIcon = true;

void Icon::update(double time)
{
	if (isExist)
	{
		if (status == Status::DEAD)
			isExist = false;
	}
}
