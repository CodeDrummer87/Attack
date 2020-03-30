#pragma once

#include "Entity.h"
#include "Animation.h"
#include <SFML\Graphics.hpp>

using namespace sf;

Entity::Entity() {}
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

void Entity::setEntity(Animation &a, int X, int Y, string n)
{
	dir = 1;
	anim = a;
	x = X;
	y = Y;
	anim.sprite.setPosition(x, y);
	name = n;
	playAnimation = false;
	isExist = true;
	status = ALIVE;
}

void Entity::update(double time)
{
	if (isExist)
	{
		if (anim.isEnd(time))
			isExist = false;
	}
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
