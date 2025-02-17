#pragma once

#include "Entity.h"

Entity::Entity()
{}

Entity::Entity(Animation &a, double x_, double y_, string name_, int dir_, bool isPlayAnimation_)
{
	dx = dy = 0.0;

	anim = a;
	x = x_;
	y = y_;
	name = name_;
	dir = dir_;
	isPlayAnimation = isPlayAnimation_;

	isExist = true;
	z_index = (short)1;

	number = 0;
	level = 1;
	status = Status::ALIVE;
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
	int offset = name == "turret" ? 77 : 42;

	if (isShell)
	{
		switch (dir)
		{
		case 0: xCoordinate; break;
		case 90: xCoordinate += offset; break;
		case 180: xCoordinate; break;
		case 270: xCoordinate -= offset; break;
		}
	}

	return xCoordinate;
}

double Entity::getCoordY(bool isShell)
{
	double yCoordinate = y;
	int offset = name == "turret" ? 77 : 42;

	if (isShell)
	{
		switch (dir)
		{
		case 0: yCoordinate -= offset; break;
		case 90: yCoordinate; break;
		case 180: yCoordinate += offset; break;
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
	return dir_ + 180 < 360 ? dir_ + 180 : dir_ - 180;
}

void Entity::resetDegrees(int &d)
{
	d = d >= 360 ? d -= 360 : d <= -1 ? d += 360 : d;
}

bool Entity::isUndeletable()
{
	return	name == "rank" ? true :
			(name == "tank" || name == "destroyed" || name == "ressurecting" || name == "ressurected") && army == "player" ? true :
			(name == "smoke" && army == "player") ? true :
			(name == "scannedZone" && army == "player") ? true : false;
}

bool Entity::isAnyGroundVehicle()
{
	return (name == "tank" ||
		name == "truck" ||
		name == "miner" ||
		name == "boss") ? true : false;
}

bool Entity::isDestroyedVehicle()
{
	return (name == "destroyed" || name == "ressurected") ? true : false;
}

bool Entity::isAnyGroundObject()
{
	return (isAnyGroundVehicle() || isDestroyedVehicle()) ? true : false;
}

bool Entity::isGroundVehicle()
{
	return (name == "tank" ||
			name == "truck" ||
			name == "miner") ? true : false;
}

bool Entity::isEnemyGroundVehicle()
{
	return (army == "enemy" && isGroundVehicle()) ? true : false;
}

bool Entity::isPlayer()
{
	return (name == "tank" && army == "player") ? true : false;
}
