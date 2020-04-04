#pragma once

#include "Entity.h"
#include "Animation.h"
#include <SFML\Graphics.hpp>

using namespace sf;

int Entity::counter = 0;

Entity::Entity() {}

Entity::Entity(Animation &a, int X, int Y)
{
	name = "smoke";
	anim = a;
	dir = 1;
	x = X;
	y = Y;
	anim.sprite.setPosition(x, y);
	isExist = playAnimation = true;
	status = ALIVE;
}

Entity::Entity(Animation &a, int X, int Y, int dir_)
{
	name = "explosion";
	anim = a;
	dir = dir_;
	x = X;
	y = Y;
	anim.sprite.setPosition(x, y);
	isExist = playAnimation = true;
	status = ALIVE;
}

Entity::~Entity() {}

void Entity::update(double time)
{
	if (isExist)
	{
		if(name == "explosion")
			if (anim.isEnd(time))
				isExist = false;
	}
}

void Entity::collideEntities(Entity *e)
{
	if (anim.getRect(dir).intersects(e->anim.getRect(e->dir)))
	{
		switch (dir)
		{
		case 1:
			break;

		case 2:
			if (checkBarrierId(e->tokenId))
			{
				traffic.right.dir = false;			e->traffic.left.dir = false;
				traffic.right.barId = e->tokenId;	e->traffic.left.barId = tokenId;
			}
			break;

		case 3:
			break;

		case 4:
			if (checkBarrierId(e->tokenId))
			{
				traffic.left.dir = false;			e->traffic.right.dir = false;
				traffic.left.barId = e->tokenId;	e->traffic.right.barId = tokenId;
			}
			break;
		}
	}
	else
	{
		if (traffic.right.barId == e->tokenId)
		{
			traffic.right.barId = 0;	traffic.right.dir = true;
		}

		if (traffic.left.barId == e->tokenId)
		{
			traffic.left.barId = 0;	traffic.left.dir = true;
		}

		if (traffic.up.barId == e->tokenId)
		{
			traffic.up.barId = 0;	traffic.up.dir = true;
		}

		if (traffic.down.barId == e->tokenId)
		{
			traffic.down.barId = 0;	traffic.down.dir = true;
		}
	}
}

bool Entity::checkBarrierId(int id)
{
	if (traffic.up.barId == id)
		return false;
	if (traffic.right.barId == id)
		return false;
	if (traffic.down.barId == id)
		return false;
	if (traffic.left.barId == id)
		return false;

	return true;
}

double Entity::getCoordX(bool isShell)
{
	double xCoordinate = x;

	if (isShell)
	{
		switch (dir)
		{
		case 1: xCoordinate; break;
		case 2: xCoordinate += 42; break;
		case 3: xCoordinate; break;
		case 4: xCoordinate -= 42; break;
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
		case 1: yCoordinate -= 42; break;
		case 2: yCoordinate; break;
		case 3: yCoordinate += 42; break;
		case 4: yCoordinate; break;
		}
	}

	return yCoordinate;
}

void Entity::draw(RenderWindow &app)
{
	anim.sprite.setPosition(x, y);
	app.draw(anim.sprite);
}
