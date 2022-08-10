#pragma once

#include "Boss.h"

Boss::Boss()
{}

Boss::Boss(BossArgs &args)
	: Enemy(args.anim, args.x, args.y, "boss", args.dir, args.isPlayAnimation, args.sExplosion, args.expFrameCount, "enemy", args.level)
{
	z_index = 3;

	hitPoints = 4;//100 + args.numberOfPlayers * 50;
	nextOilSpillageTime = 0;
	isOilSpillage = false;
}

Boss::~Boss()
{}

void Boss::update(double time)
{
	if (isDestroyed)
	{
		if (isPlayAnimation)
			isPlayAnimation = false;
	}
	else
	{
		if (hitPoints > 100)
		{
			if (status != ALIVE)
			{
				status = ALIVE;
				anim.sound.setPitch(0.9f);
			}
		}
		else if (hitPoints <= 100 && hitPoints > 0)
		{
			if (status != WOUNDED)
			{
				status = WOUNDED;
				anim.setFrames(0, 128, 128, 128, 2, anim.speed);
				anim.sound.setPitch(0.5f);
			}
		}
		else
			status = DEAD;
		//::::::::::::::::::::::::
		if (status == ALIVE)
		{
			if (x + dx > 0 && x + dx < 61 * 32)
				x += dx;
			if (y + dy > 0 && y + dy < 119 * 32)
				y += dy;
			dx = dy = 0;
		}
		else if (status == WOUNDED)
		{
			x += dx / 1.5;
			y += dy / 1.5;
			dx = dy = 0;
		}
		else
		{
			if (isTransition)
			{
				if (anim.isEnd(time))
				{
					anim.frames[0] = IntRect(0, 384, 128, 128);	//.:: Tank skeleton texture coordinates
					anim.sound.stop();
					isDestroyed = true;
				}
			}
			else
			{
				name = "destroyed";
				isPlayAnimation = true;
				anim.setFrames(0, 256, 128, 128, explosionFrameCount, 0.01);
				anim.sound.setBuffer(sExplosion);
				anim.sound.setVolume(100.f);
				isTransition = true;
				isSmoking = false;
			}
		}
		//.:: Vehicle control :::
		if (!isPlayerControl)
			controlEnemyVehicle(time);
	}
}

void Boss::checkMapCollision(string *map)
{
	if (dir == 1)
		for (int i = (y - 30) / 32; i <= (y + 40) / 32; i++)
			for (int j = (x - 2) / 32; j <= (x + 60) / 32; j++)
			{
				if (map[i][j] == 'b' || map[i][j] == 'B' || map[i][j] == 'W')
					traffic.up.dir = false;

				if (!traffic.down.dir)
					traffic.down.dir = true;
			}

	if (dir == 3)
		for (int i = (y + 20) / 32; i <= (y + 60) / 32; i++)
			for (int j = (x - 4) / 32; j <= (x + 60) / 32; j++)
			{
				if (map[i][j] == 'b' || map[i][j] == 'B' || map[i][j] == 'W')
					traffic.down.dir = false;

				if (!traffic.up.dir)
					traffic.up.dir = true;
			}

	if (dir == 4)
		for (int i = (y) / 32; i <= (y + 40) / 32; i++)
			for (int j = (x - 30) / 32; j <= (x + 20) / 32; j++)
			{
				if (map[i][j] == 'b' || map[i][j] == 'B' || map[i][j] == 'W')
					traffic.left.dir = false;

				if (!traffic.right.dir)
					traffic.right.dir = true;
			}

	if (dir == 2)
		for (int i = (y-10) / 32; i <= (y + 40) / 32; i++)
			for (int j = (x + 52) / 32; j <= (x + 64) / 32; j++)// 42  50
			{
				if (map[i][j] == 'b' || map[i][j] == 'B' || map[i][j] == 'W')
					traffic.right.dir = false;

				if (!traffic.left.dir)
					traffic.left.dir = true;
			}
}
