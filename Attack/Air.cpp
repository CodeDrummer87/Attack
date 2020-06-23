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

	attachedObject = currentAirStrikeZone;
}

Air::~Air()
{}

void Air::update(double time)
{
	dx = 0;
	dy = -0.7 * time;

	x += dx;
	y += dy;

	if (name == "fighter" && y <= attachedObject->getCoordY(false))
		if(attachedObject->isExist)
			attachedObject->isExist = false;

	if (y <= -150)
		isExist = false;
}