#pragma once

#include "Entity.h"

Entity::Entity()
{}

Entity::Entity(Animation &a, double x_, double y_, string name_, int dir_, bool isPlayAnimation_)
{
	anim = a;
	x = x_;
	y = y_;
	name = name_;
	dir = dir_;
	isPlayAnimation = isPlayAnimation_;

	isExist = true;
	z_index = 4;
}

Entity::~Entity()
{}

void Entity::draw(RenderWindow &app)
{
	anim.sprite.setPosition(x, y);
	app.draw(anim.sprite);
}

double Entity::getCoordX(bool isShell)
{
	double xCoordinate = x;

	if (isShell)
	{
		switch (dir)
		{
		case 0: xCoordinate; break;
		case 90: xCoordinate += 42; break;
		case 180: xCoordinate; break;
		case 270: xCoordinate -= 42; break;
		}
	}

	return xCoordinate;
}

double Entity::getCoordY(bool isShell)
{
	double yCoordinate = y;

	if (isShell)
	{
		switch (dir)
		{
		case 0: yCoordinate -= 42; break;
		case 90: yCoordinate; break;
		case 180: yCoordinate += 42; break;
		case 270: yCoordinate; break;
		}
	}

	return yCoordinate;
}

void Entity::setCoordX(double coord)
{
	x = coord;
}

void Entity::setCoordY(double coord)
{
	y = coord;
}

int Entity::getCounterDirection(int dir_)
{
	return dir_ + 180 <= 360 ? dir_ + 180 : dir_ - 180;
}

void Entity::resetDegrees(int &d)
{
	d = d >= 360 ? d -= 360 : d <= -1 ? d += 360 : d;
}
