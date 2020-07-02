#include "Bomb.h"

Bomb::Bomb()
{}

Bomb::Bomb(Animation &a, Animation &b, double X, double Y, string name_)
{
	name = name_;
	anim = a;
	animSpare = b;
	
	x = X;
	y = Y;
	
	anim.sprite.setPosition(x, y);
	playAnimation = isExist = true;
	status = ALIVE;

	if (!firstBomb.openPosition)
	{
		firstBomb.openPosition = true;
		firstBomb.bomb = this;
	}

	coordsTransmitted = false;
}

Bomb::~Bomb()
{}

FirstBomb Bomb::firstBomb = {false, NULL};

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
			anim.sprite.setScale(2.f, 2.f);
		}
	}
	
	if (status == WOUNDED)
	{
		if (anim.isEnd(time))
			isExist = false;
	}
}