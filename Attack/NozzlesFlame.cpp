#include "NozzlesFlame.h"

NozzlesFlame::NozzlesFlame()
{}

NozzlesFlame::NozzlesFlame(Animation& anim_, Boss* boss_)
{
	z_index = 5;

	boss = boss_;
	name = "nozzleFlame";
	isPlayAnimation = true;
	dir = boss->dir;

	number = boss->number;
	level = 1;
	army = boss->army;
	status = Status::ALIVE;
	isExist = true;

	anim = anim_;
	anim.sprite.setScale(.5f, .5f);
	firstLeft = secondLeft = thirdLeft = firstRight = secondRight = thirdRight = anim;
	wasSecondStepWent = wasThirdStepWent = false;

	setSpritesPosition();
}

NozzlesFlame::~NozzlesFlame()
{}

void NozzlesFlame::update(double time)
{
	setSpritesPosition();

	firstLeft.update(time, true, calculateAngle("left"));
	firstRight.update(time, true, calculateAngle("right"));

	if (wasSecondStepWent)
	{
		secondLeft.update(time, true, calculateAngle("left"));
		secondRight.update(time, true, calculateAngle("right"));
	}

	if (wasThirdStepWent)
	{
		thirdLeft.update(time, true, calculateAngle("left"));
		thirdRight.update(time, true, calculateAngle("right"));
	}

	if (isExist)
	{
		if (firstLeft.isEnd(time) && !wasSecondStepWent)
			wasSecondStepWent = true;

		if (secondRight.isEnd(time) && !wasThirdStepWent)
			wasThirdStepWent = true;

		if (thirdRight.isEnd(time) || !boss->isExist)
		{
			boss->isActing = false;
			isExist = false;
		}
	}
}

void NozzlesFlame::draw(RenderWindow& app)
{
	app.draw(firstLeft.sprite);
	app.draw(firstRight.sprite);

	if (wasSecondStepWent)
	{
		app.draw(secondLeft.sprite);
		app.draw(secondRight.sprite);
	}
	
	if (wasThirdStepWent)
	{
		app.draw(thirdLeft.sprite);
		app.draw(thirdRight.sprite);
	}	
}

void NozzlesFlame::setSpritesPosition()
{
	x = boss->getCoordX(false);
	y = boss->getCoordY(false);

	int d = boss->dir;

	firstLeft.sprite.setPosition(	d == 0 ? x - 63 : d == 90 ? x - 37 : d == 180 ? x + 63 : x + 37,
									d == 0 ? y + 37 : d == 90 ? y - 63 : d == 180 ? y - 37 : y + 63);

	secondLeft.sprite.setPosition(	d == 0 ? x - 63 : d == 90 ? x - 49 : d == 180 ? x + 63 : x + 49,
									d == 0 ? y + 49 : d == 90 ? y - 63 : d == 180 ? y - 49 : y + 63);

	thirdLeft.sprite.setPosition(	d == 0 ? x - 63 : d == 90 ? x - 61 : d == 180 ? x + 63 : x + 61,
									d == 0 ? y + 61 : d == 90 ? y - 63 : d == 180 ? y - 61 : y + 63);

	firstRight.sprite.setPosition(	d == 0 ? x + 63 : d == 90 ? x - 37 : d == 180 ? x - 63 : x + 37,
									d == 0 ? y + 37 : d == 90 ? y + 63 : d == 180 ? y - 37 : y - 63);

	secondRight.sprite.setPosition(	d == 0 ? x + 63 : d == 90 ? x - 49 : d == 180 ? x - 63 : x + 49,
									d == 0 ? y + 49 : d == 90 ? y + 63 : d == 180 ? y - 49 : y - 63);

	thirdRight.sprite.setPosition(	d == 0 ? x + 63 : d == 90 ? x - 61 : d == 180 ? x - 63 : x + 61,
									d == 0 ? y + 61 : d == 90 ? y + 63 : d == 180 ? y -61 : y -63);
}

float NozzlesFlame::calculateAngle(string side)
{
	float angle = (side == "right") ? -45.f : 45.f;
	return angle + boss->dir;
}
