#pragma once

#include "Shell.h"
#include "Animation.h"

#include "Enemy.h"

Shell::Shell() {}

Shell::Shell(Animation &a, Animation &b, Tank* tank)
{
	tokenId = tank->tokenId;
	dist = 0.0;
	name = "shell";
	army = tank->army;
	anim = a;
	animSpare = b;
	dir = tank->dir;
	own = tank;
	x = tank->getCoordX(true);
	y = tank->getCoordY(true);
	anim.sprite.setPosition(x, y);
	playAnimation = isExist = true;
	status = ALIVE;
	hitPoints = 0;
	level = tank->level;
	explosion = false;
}

Shell::~Shell() {}

void Shell::update(double time)
{
	if (status == ALIVE)
	{
		if (dir == 1)
		{
			dx = 0;
			dy = -0.4 * time - ((double)level / 7);
			dist -= dy;
		}
		if (dir == 2)
		{
			dy = 0;
			dx = 0.4 * time + ((double)level / 7);
			dist += dx;
		}
		if (dir == 3)
		{
			dx = 0;
			dy = 0.4 * time + ((double)level / 7);
			dist += dy;
		}
		if (dir == 4)
		{
			dy = 0;
			dx = -0.4 * time - ((double)level / 7);
			dist -= dx;
		}

		if (abs(dist) >= 350 + (float)level * 50)
			explosion = true;

		if (explosion)
		{
			status = WOUNDED;
			anim = animSpare;
			name = "explosion";
			dir = rand() % 360;
		}

		x += dx;
		y += dy;
	}
	else if (status == WOUNDED)
		if (anim.isEnd(time))
		{
			isExist = false;
			own->isShot = true;
		}
}

void Shell::allowShot()
{
	own->isShot = true;
}

void Shell::conveyExperience(int experience)
{
	if (own->army == "player" && own->status != DEAD)
		static_cast<Player*>(own)->nickDown(experience);
}

void Shell::ceaseEnemyFire()
{
	if (own->army == "enemy")
		static_cast<Enemy*>(own)->round = false;
}
