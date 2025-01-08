#include "Miner.h"

Miner::Miner()
{}

Miner::Miner(Animation& a, double x_, double y_, string name_, int dir_, bool isPlayAnimation_,
	SoundBuffer& sExplosion_, int expFrameCount, string army_, int lvl, int currentGameTime)
	: GroundVehicle(a, x_, y_, name_, dir, isPlayAnimation, sExplosion_, expFrameCount, army_, lvl)
{
	z_index = (short)2;
	rescheduleMining(currentGameTime);

	isStopped = false;
}

Miner::~Miner()
{}

void Miner::update(double time)
{
	if (isDestroyed)
	{
		if (isPlayAnimation)
			isPlayAnimation = false;
	}
	else
	{
		if (hitPoints > 1)
		{
			if (status != ALIVE)
				status = ALIVE;
		}
		else if (hitPoints == 1)
		{
			if (status != WOUNDED)
				status = WOUNDED;
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
					anim.frames[0] = IntRect(0, 128, 64, 64);
					isDestroyed = true;
				}
			}
			else
			{
				if (isStopped)
					isStopped = false;

				name = "destroyed";
				isPlayAnimation = true;
				anim.setFrames(0, 64, 64, 64, explosionFrameCount, 0.01);
				anim.sound.setBuffer(sExplosion);
				isTransition = true;
				isSmoking = false;
			}
		}
		//.:: Vehicle control :::
		if (!isStopped)
		{
			controlEnemyVehicle(time);
		}
		else isPlayAnimation = false;
	}
}

bool Miner::isInOpenArea(string* map)
{
	if (dir == 0)
		for (int i = (y - 20) / 32; i <= (y + 20) / 32; i++)
			for (int j = (x - 20) / 32; j <= (x + 30) / 32; j++)
				if (map[i][j] == 'F')
					return false;

	if (dir == 180)
		for (int i = (y + 20) / 32; i <= (y + 50) / 32; i++)
			for (int j = (x - 20) / 32; j <= (x + 30) / 32; j++)
				if (map[i][j] == 'F')
					return false;

	if (dir == 270)
		for (int i = (y) / 32; i <= (y + 30) / 32; i++)
			for (int j = (x - 16) / 32; j <= (x + 20) / 32; j++)
				if (map[i][j] == 'F')
					return false;

	if (dir == 90)
		for (int i = (y) / 32; i <= (y + 30) / 32; i++)
			for (int j = (x + 42) / 32; j <= (x + 50) / 32; j++)
				if (map[i][j] == 'F')
					return false;

	return true;
}

void Miner::rescheduleMining(int gameTime)
{
	nextRequestTime = gameTime + 20;
}
