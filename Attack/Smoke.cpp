#include "Smoke.h"

Smoke::Smoke()
{}

Smoke::Smoke(Animation &a, Tank *tank, string name_)
{
	anim = a;
	name = name_;
	
	if (name == "explosion")
	{
		dir = tank->dir;
		x = tank->getCoordX(true);
		y = tank->getCoordY(true);
	}

	if (name == "smoke")
	{
		dir = 1;
		x = tank->getCoordX(false) + 5.0f;
		y = tank->getCoordY(false) - 5.0f;
	}

	isPlayAnimation = true;
	level = 0;
	own = tank;
	anim.sprite.setPosition(x, y);
	isExist = true;
	status = ALIVE;
}

Smoke::~Smoke()
{}

void Smoke::update(double time)
{
	if (isExist)
	{
		if (name == "explosion")
			if (anim.isEnd(time))
				isExist = false;

		if (name == "smoke")
		{
			x = own->getCoordX(false) + 5.f;
			y = own->getCoordY(false) - 5.f;

			if (own->status != WOUNDED)
			{
				if (own->name == "tank")
					own->isSmoking = false;
				isExist = false;
			}
		}
	}
}
