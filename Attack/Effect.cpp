#include "Effect.h"
#include "Miner.h"

extern View view;

Effect::Effect()
{}

Effect::Effect(Animation &a, GroundVehicle* own_, string name_)
{
	z_index = (short)7;

	anim = a;
	level = 0;
	dir = 0;
	isPlayAnimation = true;
	name = name_;
	own = own_;
	constDir = getCounterDirection(own->dir);
	
	setCoordinates();

	anim.sprite.setPosition(x, y);
	anim.sound.setVolume(100.f);
	isExist = true;
	status = ALIVE;

	transparency = 10;
	if (name == "ressurection")
		anim.sound.setPitch(1.f);
}

Effect::~Effect()
{}

void Effect::update(double time)
{
	if (isExist)
	{
		if (name == "ressurection")
		{
			transparency = transparency < 70 ? ++transparency : 70;
			anim.sprite.setColor(Color(255, 255, 255, transparency));
		}

		setCoordinates();

		//.:: Mining volume depends on the distance to the camera :::::::
		if (name == "mining")
		{
			if (y > view.getCenter().y - 20 * 32 && y < view.getCenter().y + 20 * 32)
				anim.sound.setVolume(90.f);
			else if (y > view.getCenter().y - 30 * 32 && y < view.getCenter().y - 20 * 32 ||
				y < view.getCenter().y + 30 * 32 && y > view.getCenter().y + 20 * 32)
				anim.sound.setVolume(30.f);
			else
				anim.sound.setVolume(0.f);
		}
		//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

		if (anim.isEnd(time))
		{
			isExist = false;

			if (own->name == "miner")
				static_cast<Miner*>(own)->isStopped = false;

			if (own->name == "ressurecting")
				own->name = "tank";
		}
	}
}

void Effect::draw(RenderWindow &app)
{
	anim.sprite.setPosition(x, y);
	app.draw(anim.sprite);
}

void Effect::setCoordinates()
{
	if (name == "effect")
	{
		int X = own->getCoordX(false);
		int Y = own->getCoordY(false);

		x = constDir == 270 ? X - 30 : X + 30;
		y = constDir == 180 ? Y + 25 : Y - 25;
	}
	else if (name == "ressurection")
	{
		x = own->getCoordX(false);
		y = own->getCoordY(false) - 8;
	}
	else
	{
		x = own->getCoordX(false);
		y = own->getCoordY(false);

		if (name == "mining" && anim.frame > 8)
			dir++;
	}
}
