#pragma once

#include "MortarShell.h"

extern View view;

MortarShell::MortarShell()
{}

MortarShell::MortarShell(Animation &a, Animation &b, Tank *tower, double X, double Y, Tank *target, Animation &c) : Shell(a, b, tower)
{
	z_index = 5;

	x = X;
	y = Y;
	radius = 10;
	factor = 0.0f;
	dir = static_cast<TankTower*>(tower)->takeAim(target);
	currentDistance = 0.0;
	name = "mortarShell";
	sPoint = { getDistanceToTarget(target->getCoordX(false), target->getCoordY(false)), x, y };
	anim.sprite.setScale(1.1f, 1.1f);

	aTrace = c;
	aTrace.sprite.setOrigin(15.5f, 0.f);
	aTrace.sprite.setRotation(dir);
	aTrace.sprite.setScale(0.4f, 0.4f);
	aTrace.sprite.setPosition((float)x, (float)y);
	isPlayAnimation = false;

	distanceFactor = sPoint.totalDistance <= 600 ? 30.f
		: sPoint.totalDistance <= 800 ? 20.f
		: sPoint.totalDistance <= 1000 ? 10.f
		: sPoint.totalDistance <= 1200 ? 5.f : 3.5f;

	isFinishFlight = isAreaExplosionDamaged = false;
}

MortarShell::~MortarShell()
{}

void MortarShell::update(double time)
{
	if (status == ALIVE)
	{
		factor = getAccelerateFactor(sPoint.totalDistance, currentDistance);
		setShellPosition(factor);
		setTrailHeight(factor);

		dx = sin(dir * DEGTORAD) * time / factor;
		dy = -cos(dir * DEGTORAD) * time / factor;

		if (isExplosion)
		{
			status = WOUNDED;
			anim = aExplosion;
			aTrace.sprite.setColor(Color::Transparent);
			name = "mortarMineExplosion";
			isPlayAnimation = true;
			dir = rand() % 360;

			setExplosionVolume();
		}

		x += dx;
		y += dy;

		currentDistance = getDistanceToTarget(sPoint.x, sPoint.y);
		if (currentDistance >= sPoint.totalDistance - 5.0) isExplosion = true;

		aTrace.update(time, true, dir);
	}
	else if (status == WOUNDED)
		if (anim.isEnd(time))
			isExist = false;
}

void MortarShell::setExplosionVolume()
{
	if (y > view.getCenter().y - 20 * 32 && y < view.getCenter().y + 20 * 32)
		anim.sound.setVolume(50.f);
	else if (y > view.getCenter().y - 30 * 32 && y < view.getCenter().y - 20 * 32 ||
		y < view.getCenter().y + 30 * 32 && y > view.getCenter().y + 20 * 32)
		anim.sound.setVolume(15.f);
	else
		anim.sound.setVolume(0.f);
}

double MortarShell::getDistanceToTarget(double X, double Y)
{
	return sqrt(pow(x - X, 2) + pow(y - Y, 2));
}

float MortarShell::getAccelerateFactor(double totalDist, double currentDist)
{
	if (!isFinishFlight && currentDist > totalDist / 2)
		isFinishFlight = true;

	if (currentDist <= 0.00)
		return distanceFactor;
	else
	{
		currentDist = currentDist < totalDist / 2 ? currentDist : totalDist - currentDist;
		return totalDist / currentDist < distanceFactor ? totalDist / currentDist : distanceFactor;
	}
}

void MortarShell::draw(RenderWindow &app)
{
	aTrace.sprite.setPosition((float)x, (float)y);

	app.draw(aTrace.sprite);
	Entity::draw(app);
}

void MortarShell::setShellPosition(float factor)
{
	if (!isFinishFlight)
	{
		factor <= 30.0 && factor > 20.0 ? anim.setFrames(0, 0, 32, 32, 11, 1)
			: factor <= 20.0 && factor > 10 ? anim.setFrames(32, 0, 32, 32, 11, 1)
			: factor <= 10.0 && factor > 4 ? anim.setFrames(64, 0, 32, 32, 11, 1)
			: factor <= 4.0 && factor > 2.6 ? anim.setFrames(96, 0, 32, 32, 11, 1)
			: factor <= 2.6 && factor > 2.1 ? anim.setFrames(128, 0, 32, 32, 11, 1)
			: anim.setFrames(160, 0, 32, 32, 11, 1);
	}
	else
	{
		factor <= 30.0 && factor > 20.0 ? anim.setFrames(320, 0, 32, 32, 11, 1)
			: factor <= 20.0 && factor > 10 ? anim.setFrames(288, 0, 32, 32, 11, 1)
			: factor <= 10.0 && factor > 4 ? anim.setFrames(256, 0, 32, 32, 11, 1)
			: factor <= 4.0 && factor > 2.6 ? anim.setFrames(224, 0, 32, 32, 11, 1)
			: factor <= 2.6 && factor > 2.1 ? anim.setFrames(192, 0, 32, 32, 11, 1)
			: anim.setFrames(160, 0, 32, 32, 11, 1);
	}
}

void MortarShell::setTrailHeight(float factor)
{
	factor <= 30.0 && factor > 10.0 ? aTrace.sprite.setColor(Color::Transparent)
		: factor <= 10.0 && factor > 4 ? aTrace.sprite.setColor(Color::White), aTrace.setFramesDynamic(0, 80, 26, 30)
		: factor <= 4.0 && factor > 2.6 ? aTrace.setFramesDynamic(0, 60, 26, 60)
		: factor <= 2.6 && factor > 2.3 ? aTrace.setFramesDynamic(0, 40, 26, 80)
		: aTrace.setFramesDynamic(0, 0, 26, 120);
}

void MortarShell::destroyTarget(Tank *tank)
{
	if (!isAreaExplosionDamaged)
	{
		CircleShape area = CircleShape(27.f);
		area.setPosition(x, y);
		area.setOrigin(area.getGlobalBounds().width / 2, area.getGlobalBounds().height / 2);
		FloatRect a = area.getGlobalBounds();
		FloatRect t = tank->anim.sprite.getGlobalBounds();

		if (a.intersects(t))
		{
			isAreaExplosionDamaged = true;
			tank->hitPoints = 0;
		}
	}
}
