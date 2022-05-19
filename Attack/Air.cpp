#pragma once

#include "Air.h"

Air::Air()
{}

Air::Air(Animation &a, Animation &b, Entity *airSpotter, string name_)
{
	isExist = true;
	status = ALIVE;
	name = name_;
	anim = a;
	own = airSpotter;
	anim.sprite.setPosition(own->getCoordX(false), own->getCoordY(false));
	anim.sprite.setScale(1.5f, 1.5f);
	animSpare = b;
	number = static_cast<Player*>(airSpotter)->number;
	isPlayAnimation = true;
}

Air::~Air()
{}

void Air::update(double time)
{
	if (name == "target")
	{
		x = Player::airSpotter.xTargetPosition;
		y = Player::airSpotter.yTargetPosition;

		if (status == WOUNDED)
		{
			Player::airSpotter.isAirSpotter = false;
			Player::airSpotter.currentPlayer = NULL;

			name = "zone";
			anim = animSpare;
			anim.sprite.setPosition(x, y);
			anim.sprite.setScale(1.5f, 1.5f);

			status = ALIVE;
		}
	}

	if (name == "zone")
	{
		if (status == WOUNDED)
			isExist = false;
	}
}

Entity* Air::getOwn()
{
	return own;
}
