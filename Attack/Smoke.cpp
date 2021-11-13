#include "Smoke.h"

extern View view;

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

		//.:: Explosion volume depends on the distance to the camera :::::::
		if (y > view.getCenter().y - 20 * 32 && y < view.getCenter().y + 20 * 32)
			anim.sound.setVolume(50.f);
		else if (y > view.getCenter().y - 30 * 32 && y < view.getCenter().y - 20 * 32 ||
			y < view.getCenter().y + 30 * 32 && y > view.getCenter().y + 20 * 32)
			anim.sound.setVolume(15.f);
		else
			anim.sound.setVolume(0.f);
		//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	}

	if (name == "smoke")
	{
		dir = 1;
		x = tank->getCoordX(false) + 2.f;
		y = tank->getCoordY(false) + 2.f;
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
			x = own->getCoordX(false) + 2.f;
			y = own->getCoordY(false) + 2.f;

			if (own->status == ALIVE)
			{
				if (own->name == "tank")
					own->isSmoking = false;
				isExist = false;
			}
		}
	}
}
