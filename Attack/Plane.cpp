#pragma once

#include "Plane.h"

Plane::Plane()
{}

Plane::Plane(Animation &a, Animation &b, Animation &c, double X, double Y, string name_, Entity *attachedObject_)
{
	z_index = (short)6;

	name = name_;
	attachedObject = attachedObject_;

	aEssential = a;
	aTrace = b;
	aJetFlame = c;

	x = X;
	y = Y;

	aEssential.sprite.setPosition((float)x, (float)y);
	aTrace.sprite.setScale(1.31f, 1.31f);
	aTrace.sprite.setPosition((float)x, (float)y + 100);
	aJetFlame.sprite.setPosition((float)x, (float)y + 150);

	isPlayAnimation = isExist = true;

	if (!leader.openPosition)
	{
		leader.openPosition = true;
		leader.plane = this;
		leader.bombStatus = ABOARD;
	}
}

Plane::~Plane()
{}

Leading Plane::leader = { false, NULL };

void Plane::update(double time)
{
	dy = -0.7 * time;
	y += dy;

	if (y <= attachedObject->getCoordY(false) + 300)
	{
		if (leader.plane == this && leader.bombStatus == ABOARD)
			leader.bombStatus = DROPPED;

		if (attachedObject->isExist)
			attachedObject->status = WOUNDED;
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
