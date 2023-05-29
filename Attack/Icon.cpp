#pragma once
#include "Icon.h"


Icon::Icon()
{}

Icon::Icon(IconAnim icons[], double X, double Y, int currentGameTime)
{
	z_index = 4;

	srand(std::time(NULL));
	removalTime = currentGameTime + 40;
	int index;
	if (isFirstIcon)
	{
		index = 0;
		isFirstIcon = false;
		removalTime = 0;
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

	spawnTimer = currentGameTime + 30;
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
