#include "Smoke.h"

extern View view;

Smoke::Smoke()
{}

Smoke::Smoke(Animation &a, GroundVehicle *vehicle, string name_)
{
	anim = a;
	name = name_;
	level = 0;
	army = vehicle->army;

	if (name == "explosion")
	{
		dir = vehicle->dir;
		x = vehicle->getCoordX(true);
		y = vehicle->getCoordY(true);

		//.:: Explosion volume depends on the distance to the camera :::::::
		if (army == "enemy")
		{
			if (y > view.getCenter().y - 20 * 32 && y < view.getCenter().y + 20 * 32)
				anim.sound.setVolume(50.f);
			else if (y > view.getCenter().y - 30 * 32 && y < view.getCenter().y - 20 * 32 ||
				y < view.getCenter().y + 30 * 32 && y > view.getCenter().y + 20 * 32)
				anim.sound.setVolume(15.f);
			else
				anim.sound.setVolume(0.f);
		}
		//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	}

	if (name == "smoke")
	{
		dir = 1;
		x = vehicle->getCoordX(false) + 2.f;
		y = vehicle->getCoordY(false) + 2.f;
		if (vehicle->status == DEAD) level = 1;
	}

	isPlayAnimation = true;	
	own = vehicle;
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

			if (level == 0)
			{
				if (own->status != WOUNDED)
				{
					static_cast<GroundVehicle*>(own)->isSmoking = false;
					isExist = false;
				}
			}

			if (own->isDrowned)
				isExist = false;
		}
	}
}
