#pragma once
#include "Icon.h"


Icon::Icon()
{}

Icon::Icon(IconAnim icons[], double X, double Y, int appearanceTime)
{
	z_index = 4;
	++iconCounter;

	srand(std::time(NULL));

	int index;
	if (isFirstIcon)
	{
		index = 0;
		isFirstIcon = false;
	}
	else
		index = rand() % (sizeof(icons) - 1) + 1;

	x = X;
	y = Y;
	anim = icons[index].anim;
	iconType = icons[index].iconType;
	isExist = true;

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
int Icon::iconCounter = 0;

void Icon::update(double time)
{
	if (isExist)
	{
		if (status == Status::DEAD)
		{
			--iconCounter;
			isExist = false;
		}
	}
}
