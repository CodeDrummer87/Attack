#pragma once

#include "Bomb.h"

Bomb::Bomb()
{}

Bomb::Bomb(Animation &a, Animation &b, double X, double Y, string name_)
{
	name = name_;
	anim = a;
	animSpare = b;
	army = "player";

	animSpare.sound.setLoop(false);
	animSpare.sound.setPitch(0.78f);

	x = X;
	y = Y;

	anim.sprite.setScale(0.14f, 0.14f);
	anim.sprite.setPosition(x, y);
	isPlayAnimation = isExist = true;
	status = ALIVE;

	if (!firstBomb.isOpenPosition)
	{
		firstBomb.isOpenPosition = true;
		firstBomb.bomb = this;
	}

	coordsTransmitted = false;
}

Bomb::~Bomb()
{}

FirstBomb Bomb::firstBomb = { false, NULL };

void Bomb::update(double time)
{
	if (status == ALIVE)
	{
		dy = -0.09 * time;
		y += dy;

		if (anim.isEnd(time))
		{
			if (firstBomb.bomb == this)
				firstBomb.bomb = NULL;

			status = WOUNDED;
			anim = animSpare;
			name = "explosion";
			anim.sprite.setScale(2.2f, 2.2f);
		}
	}

	if (status == WOUNDED)
	{
		if (anim.isEnd(time))
		{
			isExist = false;
			Player::airSpotter.xTargetPosition = 0.0;
			Player::airSpotter.yTargetPosition = 0.0;
		}
	}
}
