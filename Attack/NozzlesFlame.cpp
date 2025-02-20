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
			boss->isAiming = false;
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

	//.:: boss-dir = 270
	firstLeft.sprite.setPosition(x + 37, y + 63);
	secondLeft.sprite.setPosition(x + 49, y + 63);
	thirdLeft.sprite.setPosition(x + 61, y + 63);

	firstRight.sprite.setPosition(x + 37, y - 63);
	secondRight.sprite.setPosition(x + 49, y - 63);
	thirdRight.sprite.setPosition(x + 61, y - 63);

	//.:: boss-dir = 0
	/*firstLeft.sprite.setPosition(x - 63, y + 37);
	secondLeft.sprite.setPosition(x - 63, y + 49);
	thirdLeft.sprite.setPosition(x - 63, y + 61);

	firstRight.sprite.setPosition(x + 63, y + 37);
	secondRight.sprite.setPosition(x + 63, y + 49);
	thirdRight.sprite.setPosition(x + 63, y + 61);*/

	//.:: boss-dir = 90
	/*firstLeft.sprite.setPosition(x - 37, y - 63);
	secondLeft.sprite.setPosition(x - 49, y - 63);
	thirdLeft.sprite.setPosition(x - 61, y - 63);

	firstRight.sprite.setPosition(x - 37, y + 63);
	secondRight.sprite.setPosition(x - 49, y + 63);
	thirdRight.sprite.setPosition(x - 61, y + 63);*/

	//.:: boss-dir = 180
	/*firstLeft.sprite.setPosition(x + 63, y - 37);
	secondLeft.sprite.setPosition(x + 63, y - 49);
	thirdLeft.sprite.setPosition(x + 63, y - 61);

	firstRight.sprite.setPosition(x - 63, y - 37);
	secondRight.sprite.setPosition(x - 63, y - 49);
	thirdRight.sprite.setPosition(x - 63, y - 61);*/
}

float NozzlesFlame::calculateAngle(string side)
{
	float angle = (side == "right") ? -45.f : 45.f;
	return angle + boss->dir;
}
