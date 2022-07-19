#pragma once

#include "EnemyPlane.h"

EnemyPlane::EnemyPlane()
{}

EnemyPlane::EnemyPlane(Animation &a, Animation &b, Animation &c, double X, double Y, string name_, double dropPoint_, int mapHeight_)
{
	z_index = (short)6;

	name = name_;
	mapHeight = mapHeight_ * 32;
	dropPoint = dropPoint_;

	aEssential = a;
	aTrace = b;
	aJetFlame = c;

	x = X;
	y = Y;

	aEssential.sprite.setPosition((float)x, (float)y);
	aTrace.sprite.setScale(1.40f, 1.40f);
	aTrace.sprite.setPosition((float)x, (float)y + 127);
	aJetFlame.sprite.setPosition((float)x - 2, (float)y + 135);

	isPlayAnimation = isExist = true;

	bombStatus = BombStatus::ABOARD;
}

EnemyPlane::~EnemyPlane()
{}

Player* EnemyPlane::target = NULL;

void EnemyPlane::update(double time)
{
	dy = 0.7 * time;
	y += dy;

	if (bombStatus == ABOARD && y >= dropPoint - 300.0)
		bombStatus = DROPPED;

	if (y >= mapHeight + 200)
		isExist = false;

	aTrace.update(time, true, 3);
	aJetFlame.update(time, true, 3);
}

void EnemyPlane::draw(RenderWindow &app)
{
	aEssential.sprite.setPosition((float)x, (float)y);
	aTrace.sprite.setPosition((float)x, (float)y - 127);
	aJetFlame.sprite.setPosition((float)x - 2, (float)y - 135);

	app.draw(aEssential.sprite);
	app.draw(aTrace.sprite);
	app.draw(aJetFlame.sprite);
}
