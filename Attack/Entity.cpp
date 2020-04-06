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
			if (dy != 0)
			{
				if (traffic.up.barId == 0 && checkBarrierId(1, e->tokenId))
				{
					traffic.up.dir = false;
					traffic.up.barId = e->tokenId;

					if (e->dy == 0)
					{
						e->traffic.down.dir = false;
						e->traffic.down.barId = tokenId;
					}
				}
			}
			break;

		case 2:
			if (dx != 0)
			{
				if (traffic.right.barId == 0 && checkBarrierId(2, e->tokenId))
				{
					traffic.right.dir = false;
					traffic.right.barId = e->tokenId;

					if (e->dx == 0)
					{
						e->traffic.left.dir = false;
						e->traffic.left.barId = tokenId;
					}
				}
			}
			break;

		case 3:
			if (dy != 0)
			{
				if (traffic.down.barId == 0 && checkBarrierId(3, e->tokenId))
				{
					traffic.down.dir = false;
					traffic.down.barId = e->tokenId;

					if (e->dy == 0)
					{
						e->traffic.up.dir = false;
						e->traffic.up.barId = tokenId;
					}
				}
			}
			break;

		case 4:
			if (dx != 0)
			{
				if (traffic.left.barId == 0 && checkBarrierId(4, e->tokenId))
				{
					traffic.left.dir = false;
					traffic.left.barId = e->tokenId;

					if (e->dx == 0)
					{
						e->traffic.right.dir = false;
						e->traffic.right.barId = tokenId;
					}
				}
			}
			break;
		}
	}
	else
	{
		if (!traffic.right.dir)
		{		
			if (traffic.right.barId == e->tokenId)
			{
				traffic.right.barId = 0;	traffic.right.dir = true;
			}
		}

		if (!traffic.left.dir)
		{
			if (traffic.left.barId == e->tokenId)
			{
				traffic.left.barId = 0;		traffic.left.dir = true;
			}
		}

		if (!traffic.up.dir)
		{
			if (traffic.up.barId == e->tokenId)
			{
				traffic.up.barId = 0;	traffic.up.dir = true;
			}
		}

		if (!traffic.down.dir)
		{
			if (traffic.down.barId == e->tokenId)
			{
				traffic.down.barId = 0;	traffic.down.dir = true;
			}
		}
	}
}

void Entity::toDamageEntity(Entity *e)
{
	if (anim.getShellRect().intersects(e->anim.getRect(e->dir)))
	{
		// to Damage tank
	}
}

/// The method exists to protect against repeated intersection
/// with an already intersecting object.
/// Checking goes in all directions except one (first parameter)
bool Entity::checkBarrierId(int dir, int id)
{
	bool check = true;
	if (traffic.up.dir != dir && traffic.up.barId == id)
		check = false;
	else if (traffic.right.dir != dir && traffic.right.barId == id)
		check = false;
	else if (traffic.down.dir != dir && traffic.down.barId == id)
		check = false;
	else if (traffic.left.dir != dir && traffic.left.barId == id)
		check = false;

	return check;
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
