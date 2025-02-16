#include "Miner.h"

Miner::Miner()
{}

Miner::Miner(Animation& a, double x_, double y_, SoundBuffer& sExplosion_, int currentGameTime)
	: GroundVehicle(a, x_, y_, "miner", 270, true, sExplosion_, 12, "enemy", 1)
{
	z_index = (short)2;
	rescheduleMining(currentGameTime);

	isStopped = false;
	isInRadarCoverageArea = false;
	speedBonus = 0.2f;
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

	if (status != Status::DEAD)
	{
		z_index = isInRadarCoverageArea ? 3 : 2;
		anim.sprite.setColor(isInRadarCoverageArea ? Color(0, 255, 0, 210) : Color::White);
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
