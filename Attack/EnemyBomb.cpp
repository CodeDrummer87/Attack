#pragma once

#include "EnemyBomb.h"

EnemyBomb::EnemyBomb()
{}

EnemyBomb::EnemyBomb(Animation &a, Animation &b, double X, double Y, string name_)
{
	dir = 3;
	name = name_;
	anim = a;
	bombExplosion = b;
	army = "enemy";

	bombExplosion.sound.setLoop(false);
	bombExplosion.sound.setPitch(0.78f);

	x = X;
	y = Y;

	anim.sprite.setScale(0.14f, 0.14f);
	anim.sprite.setPosition(x, y);
	isPlayAnimation = isExist = true;
	status = ALIVE;

	coordsTransmitted = false;
}

EnemyBomb::~EnemyBomb()
{}

void EnemyBomb::update(double time)
{
	if (status == ALIVE)
	{
		dy = 0.09 * time;
		y += dy;

		if (anim.isEnd(time))
		{
			status = WOUNDED;
			anim = bombExplosion;
			name = "bombExplosion";
			anim.sprite.setScale(1.2f, 1.2f);
		}
	}

	if (status == WOUNDED)
		if (anim.isEnd(time))
			isExist = false;
}
