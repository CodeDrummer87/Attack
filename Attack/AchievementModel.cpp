#pragma once

#include "AchievementModel.h"

AchievementModel::AchievementModel()
{}

AchievementModel::AchievementModel(Animation &a, Tank* own_, string name_)
{
	z_index = (short)6;

	anim = a;
	level = 0;
	dir = 0;
	isPlayAnimation = true;
	name = name_;
	own = own_;
	constDir = getCounterDirection(own->dir);
	
	setCoordinates();

	anim.sprite.setPosition(x, y);
	anim.sound.setVolume(100.f);
	isExist = true;
	status = ALIVE;
}

AchievementModel::~AchievementModel()
{}

void AchievementModel::update(double time)
{
	if (isExist)
	{
		setCoordinates();

		if (anim.isEnd(time))
			isExist = false;
	}
}

void AchievementModel::draw(RenderWindow &app)
{
	anim.sprite.setPosition(x, y);
	app.draw(anim.sprite);
}

void AchievementModel::setCoordinates()
{
	if (name == "effect")
	{
		int X = own->getCoordX(false);
		int Y = own->getCoordY(false);

		x = constDir == 270 ? X - 30 : X + 30;
		y = constDir == 180 ? Y + 25 : Y - 25;
	}
	else
	{
		x = own->getCoordX(false);
		y = own->getCoordY(false);
	}
}
