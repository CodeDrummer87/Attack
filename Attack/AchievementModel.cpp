#pragma once

#include "AchievementModel.h"

AchievementModel::AchievementModel()
{}

AchievementModel::AchievementModel(Animation &a, Tank* own_, string name_)
{
	z_index = (short)6;

	anim = a;
	level = 0;
	dir = 1;
	isPlayAnimation = true;
	name = name_;
	own = own_;
	x = own->getCoordX(false);
	y = own->getCoordY(false);
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
		x = own->getCoordX(false);
		y = own->getCoordY(false);

		if (anim.isEnd(time))
			isExist = false;
	}
}

void AchievementModel::draw(RenderWindow &app)
{
	anim.sprite.setPosition(x, y);
	app.draw(anim.sprite);
}
