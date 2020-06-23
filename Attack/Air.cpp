#include "Air.h"

Air::Air()
{}

Air::Air(Animation &a, int X, int Y, int dir_, string name_, Entity *currentAirStrikeZone)
{
	anim = a;
	name = name_;
	x = X;
	y = Y;
	dir = dir_;
	anim.sprite.setPosition(x, y);
	playAnimation = isExist = true;
	status = ALIVE;

	if (name == "fighter")
	{
		a.sound.setLoop(false);
	}

	currentZone = currentAirStrikeZone;
}

Air::~Air()
{}

void Air::update(double time)
{
	dx = 0;
	dy = -0.7 * time;

	x += dx;
	y += dy;

	if (y <= currentZone->getCoordY(false))
		if(currentZone->isExist)
			currentZone->isExist = false;

	if (y <= -150)
		isExist = false;
}