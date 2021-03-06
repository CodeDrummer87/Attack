#include "Plane.h"

Plane::Plane()
{}

Plane::Plane(Animation &a, Animation &b, Animation &c, double X, double Y, string name_, Entity *attachedObject_)
{
	name = name_;
	attachedObject = attachedObject_;

	aEssential = a;
	aTrace = b;
	aJetFlame = c;

	x = X;
	y = Y;

	aEssential.sprite.setPosition((float)x, (float)y);
	aTrace.sprite.setPosition((float)x, (float)y + 100);
	aJetFlame.sprite.setPosition((float)x, (float)y + 150);

	playAnimation = isExist = true;
	bombStatus = ABOARD;

	if (!leader.openPosition)
	{
		leader.openPosition = true;
		leader.plane = this;
	}
}

Plane::~Plane()
{}

Leading Plane::leader = {false, NULL};

void Plane::update(double time)
{
	dy = -0.7 * time;
	y += dy;

	if (y <= attachedObject->getCoordY(false) + 300)
	{
		if (bombStatus == ABOARD)
			bombStatus = DROPPED;

		if (attachedObject->isExist)
			attachedObject->isExist = false;
	}

	if (y <= -150)
	{
		if (leader.plane == this)
		{
			leader.plane = NULL;
			leader.openPosition = false;
		}

		isExist = false;
	}

	aTrace.update(time, true, 1);
	aJetFlame.update(time, true, 1);
}

void Plane::draw(RenderWindow &app)
{
	aEssential.sprite.setPosition((float)x, (float)y);
	aTrace.sprite.setPosition((float)x, (float)y + 100);
	aJetFlame.sprite.setPosition((float)x, (float)y + 150);

	app.draw(aEssential.sprite);
	app.draw(aTrace.sprite);
	app.draw(aJetFlame.sprite);
}