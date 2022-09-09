#include "Smoke.h"

extern View view;

Smoke::Smoke()
{}

Smoke::Smoke(Animation &a, GroundVehicle *vehicle, string name_)
{
	z_index = (short)3;

	anim = a;
	name = name_;
	level = 0;
	army = vehicle->army;

	if (name == "explosion" || name == "dustClap")
	{
		dir = vehicle->dir;
		x = vehicle->getCoordX(true);
		y = vehicle->getCoordY(true);

		if (name == "dustClap")
		{
			z_index = 3;
			anim.sprite.setScale(1.4f, 1.4f);
		}

		//.:: Explosion volume depends on the distance to the camera :::::::
		if (army == "enemy")
			setExplosionVolume();
	}

	if (name == "smoke")
	{
		z_index = vehicle->z_index == (short)3 ? (short)4 : (short)2;
		if (z_index == (short)4)
			anim.sprite.setScale(1.7f, 1.7f);

		dir = 0;
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

Smoke::Smoke(Animation &a, GroundVehicle *vehicle, string name_, short numberOfCannon_)
{
	z_index = (short)3;

	anim = a;
	name = name_;
	level = 0;
	army = vehicle->army;
	isPlayAnimation = true;
	own = vehicle;
	dir = vehicle->dir;
	anim.sprite.setPosition(x, y);
	isExist = true;
	status = ALIVE;
	numberOfCannon = numberOfCannon_;

	double X = own->getCoordX(true);
	double Y = own->getCoordY(true);

	if (numberOfCannon == (short)1)
	{
		x = dir == 0 ? X -= 8 : dir == 90 ? X += 32 : dir == 180 ? X -= 7 : X -= 30;
		y = dir == 0 ? Y -= 32 : dir == 90 ? Y -= 8 : dir == 180 ? Y += 32 : Y -= 8;
	}
	else
	{
		x = dir == 0 ? X += 8 : dir == 90 ? X += 32 : dir == 180 ? X += 8 : X -= 30;
		y = dir == 0 ? Y -= 32 : dir == 90 ? Y += 7 : dir == 180 ? Y += 32 : Y += 7;
	}

	setExplosionVolume();
}

Smoke::Smoke(Animation &a, double X, double Y, string name_)
{
	z_index = 4;

	anim = a;
	x = X;
	y = Y;
	name = name_;
	level = 0;
	army = "";
	isPlayAnimation = true;
	own = NULL;
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
		if (name == "explosion" || name == "dustClap")
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

		if (name == "dustClap")
		{
			x = own->getCoordX(false);
			y = own->getCoordY(false);
		}
	}
}

void Smoke::setExplosionVolume()
{
	if (y > view.getCenter().y - 20 * 32 && y < view.getCenter().y + 20 * 32)
		anim.sound.setVolume(50.f);
	else if (y > view.getCenter().y - 30 * 32 && y < view.getCenter().y - 20 * 32 ||
		y < view.getCenter().y + 30 * 32 && y > view.getCenter().y + 20 * 32)
		anim.sound.setVolume(15.f);
	else
		anim.sound.setVolume(0.f);
}
