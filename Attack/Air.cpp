#pragma once

#include "Air.h"
#include "Player.h"

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
	anim.sprite.setScale(2.5f, 2.5f);
	animSpare = b;
	tokenId = airSpotter->tokenId;
}

Air::~Air()
{}

void Air::update(double time)
{
	if (name == "target")
	{
		x = static_cast<Player*>(own)->xTargetPosition;
		y = static_cast<Player*>(own)->yTargetPosition;

		if (status == WOUNDED)
		{
			name = "zone";
			anim = animSpare;
			anim.sprite.setPosition(x, y);
			anim.sprite.setScale(2.5f, 2.5f);

			static_cast<Player*>(own)->xTargetPosition = 0;
			static_cast<Player*>(own)->yTargetPosition = 0;

			status = DEAD;
		}
	}
}