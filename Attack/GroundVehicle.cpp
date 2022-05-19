#pragma once

#include "GroundVehicle.h"
#include "Tank.h"

extern View view;

GroundVehicle::GroundVehicle()
{}

GroundVehicle::GroundVehicle(Animation &anim, double x_, double y_, string name_, int dir_, bool isPlayAnimation_,
	Animation &aExplosion, string army_, int level_)
	: Entity(anim, x_, y_, name_, dir_, isPlayAnimation_)
{
	army = army_;
	level = level_;
	status = ALIVE;
	aVehicleExplosion = aExplosion;

	speedBonus = 0.0f;
	isDestroyed = isTransition = drowning = isSmoking = isDrowned = isShowRepair = isPlayerControl = false;
	hitPoints = level + 1;
	toUp = toDown = toRight = toLeft = 0;

	pusher = NULL;

	traffic.up.dir = true;		traffic.up.barId = 0;
	traffic.right.dir = true;	traffic.right.barId = 0;
	traffic.down.dir = true;	traffic.down.barId = 0;
	traffic.left.dir = true;	traffic.left.barId = 0;

	number = ++counter;

	reachDist = 0.0;
	vehicleSpeed = level % 2 == 0 ? 0.1f : 0.08f;
}

GroundVehicle::~GroundVehicle()
{}

int GroundVehicle::counter = 0;

void GroundVehicle::update(double time)
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
			{
				status = ALIVE;
				anim.sound.setPitch(0.9f);
			}
		}
		else if (hitPoints == 1)
		{
			if (status != WOUNDED)
			{
				status = WOUNDED;
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
					anim.frames[0] = IntRect(0, 128, 64, 64);	//.:: Tank skeleton texture coordinates
					anim.sound.stop();
					isDestroyed = true;
				}
			}
			else
			{
				name = "destroyed";
				isPlayAnimation = true;
				anim = aVehicleExplosion;
				isTransition = true;
				isSmoking = false;
			}
		}
		//.:: Vehicle control :::
		if (!isPlayerControl)
			controlEnemyVehicle(time);
	}
}

void GroundVehicle::accelerate(int dir_, double acc)
{
	acc = (acc > 0) ? acc + speedBonus : acc - speedBonus;

	isPlayAnimation = true;
	dir = dir_;

	switch (dir)
	{
	case 1:
		toLeft = toRight = 0;
		if (traffic.up.dir)
			toUp = acc - ((double)level / 100);
		else
			toUp = 0;
		break;

	case 2:
		toUp = toDown = 0;
		if (traffic.right.dir)
			toRight = acc + ((double)level / 100);
		else
			toRight = 0;
		break;

	case 3:
		toLeft = toRight = 0;
		if (traffic.down.dir)
			toDown = acc + ((double)level / 100);
		else
			toDown = 0;
		break;

	case 4:
		toUp = toDown = 0;
		if (traffic.left.dir)
			toLeft = acc - ((double)level / 100);
		else
			toLeft = 0;
		break;
	}

	dx += toLeft + toRight;
	if (army == "player")
	{
		if (y < view.getCenter().y - 510)
			dy += toDown;
		else if (y > view.getCenter().y + 510)
			dy += toUp;
		else
			dy += toUp + toDown;
	}
	else
		dy += toUp + toDown;

	toUp = toRight = toDown = toLeft = 0;
}

bool GroundVehicle::makeSureDestroyed()
{
	return isDestroyed;
}

void GroundVehicle::checkVehiclesCollision(GroundVehicle *t)
{
	switch (dir)
	{
	case 1:
		if (y <= t->y + 52 && x > t->x - 32 && x < t->x + 32 && y > t->y)
		{
			if (army == "enemy")
			{
				traffic.up.dir = false;
				traffic.up.barId = t->number;
			}
			else
				dy = 0;
		}
		else if (y > t->y + 52 && x > t->x - 32 && x < t->x + 32 && y > t->y)
			if (!traffic.up.dir && traffic.up.barId == t->number && army == "enemy")
			{
				traffic.up.dir = true;
				traffic.up.barId = 0;
			}
		break;

	case 2:
		if (x + 52 >= t->x && y > t->y - 32 && y < t->y + 32 && x < t->x)
		{
			if (army == "enemy")
			{
				traffic.right.dir = false;
				traffic.right.barId = t->number;
			}
			else
				dx = 0;
		}
		else if (x + 52 < t->x && y > t->y - 32 && y < t->y + 32 && x < t->x)
			if (!traffic.right.dir && traffic.right.barId == t->number && army == "enemy")
			{
				traffic.right.dir = true;
				traffic.right.barId = 0;
			}
		break;

	case 3:
		if (y + 52 >= t->y && x > t->x - 32 && x < t->x + 32 && y < t->y)
		{
			if (army == "enemy")
			{
				traffic.down.dir = false;
				traffic.down.barId = t->number;
			}
			else
				dy = 0;
		}
		else if (y + 52 < t->y && x > t->x - 32 && x < t->x + 32 && y < t->y)
			if (!traffic.down.dir && traffic.down.barId == t->number && army == "enemy")
			{
				traffic.down.dir = true;
				traffic.down.barId = 0;
			}
		break;

	case 4:
		if (x <= t->x + 52 && y > t->y - 32 && y < t->y + 32 && x > t->x)
		{
			if (army == "enemy")
			{
				traffic.left.dir = false;
				traffic.left.barId = t->number;
			}
			else
				dx = 0;
		}
		else if (x > t->x + 52 && y > t->y - 32 && y < t->y + 32 && x > t->x)
			if (!traffic.left.dir && traffic.left.barId == t->number && army == "enemy")
			{
				traffic.left.dir = true;
				traffic.left.barId = 0;
			}
		break;
	}
}

bool GroundVehicle::makeSureVehicleCollision(GroundVehicle *t)
{
	switch (dir)
	{
	case 1:
		if (y <= t->y + 52 && x > t->x - 32 && x < t->x + 32 && y > t->y)
			return true;

	case 2:
		if (x + 52 >= t->x && y > t->y - 32 && y < t->y + 32 && x < t->x)
			return true;

	case 3:
		if (y + 52 >= t->y && x > t->x - 32 && x < t->x + 32 && y < t->y)
			return true;

	case 4:
		if (x <= t->x + 52 && y > t->y - 32 && y < t->y + 32 && x > t->x)
			return true;
	}

	return false;
}

void GroundVehicle::getAreaDamage(Area *area, string *map)
{
	FloatRect a = this->anim.sprite.getGlobalBounds();
	FloatRect b = area->area.getGlobalBounds();

	if (a.intersects(b))
		if (this->hitPoints > 0)
		{
			this->hitPoints = 0;
			if (area->army != army)
			{
				area->victims++;
				area->totalExperience += this->level;
			}
		}

	if (!area->isTerrainDestroyed)
	{
		area->isTerrainDestroyed = true;
		for (int i = b.top / 32 - b.height / 1.1 / 32; i < b.top / 32 + b.height / 1.1 / 32; i++)
			for (int j = b.left / 32 - b.width / 15 / 32; j < b.left / 32 + b.width / 32; j++)
			{
				if (i > 0 && j > 0)
					if (map[i][j] == 'b' || map[i][j] == 'F')
						map[i][j] = ' ';
			}
	}
}

void GroundVehicle::checkMapCollision(string * map)
{
	if (isPlayerControl)
	{
		if (dy < 0)
			for (int i = (y - 20) / 32; i <= (y + 20) / 32; i++)
				for (int j = (x - 2) / 32; j <= (x + 30) / 32; j++)
					if (map[i][j] == 'b' || map[i][j] == 'B' || map[i][j] == 'W')
						dy = 0;

		if (dy > 0)
			for (int i = (y + 20) / 32; i <= (y + 50) / 32; i++)
				for (int j = (x - 2) / 32; j <= (x + 30) / 32; j++)
					if (map[i][j] == 'b' || map[i][j] == 'B' || map[i][j] == 'W')
						dy = 0;

		if (dx < 0)
			for (int i = (y) / 32; i <= (y + 30) / 32; i++)
				for (int j = (x - 16) / 32; j <= (x + 20) / 32; j++)
					if (map[i][j] == 'b' || map[i][j] == 'B' || map[i][j] == 'W')
						dx = 0;

		if (dx > 0)
			for (int i = (y) / 32; i <= (y + 30) / 32; i++)
				for (int j = (x + 42) / 32; j <= (x + 50) / 32; j++)
					if (map[i][j] == 'b' || map[i][j] == 'B' || map[i][j] == 'W')
						dx = 0;
	}
	else
	{
		if (dir == 1)
			for (int i = (y - 20) / 32; i <= (y + 20) / 32; i++)
				for (int j = (x - 2) / 32; j <= (x + 30) / 32; j++)
				{
					if (map[i][j] == 'b' || map[i][j] == 'B' || map[i][j] == 'W')
						traffic.up.dir = false;

					if (!traffic.down.dir)
						traffic.down.dir = true;
				}

		if (dir == 3)
			for (int i = (y + 20) / 32; i <= (y + 50) / 32; i++)
				for (int j = (x - 2) / 32; j <= (x + 30) / 32; j++)
				{
					if (map[i][j] == 'b' || map[i][j] == 'B' || map[i][j] == 'W')
						traffic.down.dir = false;

					if (!traffic.up.dir)
						traffic.up.dir = true;
				}

		if (dir == 4)
			for (int i = (y) / 32; i <= (y + 30) / 32; i++)
				for (int j = (x - 16) / 32; j <= (x + 20) / 32; j++)
				{
					if (map[i][j] == 'b' || map[i][j] == 'B' || map[i][j] == 'W')
						traffic.left.dir = false;

					if (!traffic.right.dir)
						traffic.right.dir = true;
				}

		if (dir == 2)
			for (int i = (y) / 32; i <= (y + 30) / 32; i++)
				for (int j = (x + 42) / 32; j <= (x + 50) / 32; j++)
				{
					if (map[i][j] == 'b' || map[i][j] == 'B' || map[i][j] == 'W')
						traffic.right.dir = false;

					if (!traffic.left.dir)
						traffic.left.dir = true;
				}
	}
}

void GroundVehicle::checkIconCollision(string map[], Sound &sound)
{
	for (int i = (anim.getRect(dir).top + 15) / 32; i < (y + anim.getRect(dir).height) / 32; i++)
		for (int j = (anim.getRect(dir).left + 14) / 32; j < (x + anim.getRect(dir).width) / 32; j++)
		{
			if (map[i][j] == 'R')
			{
				if (hitPoints < 1 + level)
				{
					sound.play();
					++hitPoints;
					isShowRepair = true;
					map[i][j] = ' ';
				}
			}
		}
}

void GroundVehicle::updateDestinationDistance()
{
	reachDist = 0.0;
	destinationDist = abs(y - x) + (level + number) * 2;
	while (destinationDist > 1200)
		destinationDist /= 2;
	if (destinationDist < 300)
		destinationDist += 400;
}

void GroundVehicle::controlEnemyVehicle(double time)
{
	if (name != "destroyed")
	{
		switch (dir)
		{
		case 1:
			if (traffic.up.dir)
				accelerate(1, -vehicleSpeed * time);
			else
				changeDir();
			break;
		case 2:
			if (traffic.right.dir)
				accelerate(2, vehicleSpeed * time);
			else
				changeDir();
			break;
		case 3:
			if (traffic.down.dir)
				accelerate(dir, vehicleSpeed * time);
			else
				changeDir();
			break;
		case 4:
			if (traffic.left.dir)
				accelerate(dir, -vehicleSpeed * time);
			else
				changeDir();
			break;
		}

		reachDist += vehicleSpeed * time;
		if (reachDist >= destinationDist)
		{
			changeDir();
			updateDestinationDistance();
		}
	}
}

void GroundVehicle::changeDir()
{
	srand(time(NULL));

	int k = rand() % 100 + 1;
	if (k <= 25)
	{
		dir++;
		if (dir > 4)
			dir = 1;
	}
	else if (k > 25 && k <= 50)
	{
		dir--;
		if (dir < 1)
			dir = 4;
	}
	else if (k > 50 && k <= 75)
	{
		dir += 2;
		if (dir > 4)
			dir -= 4;
	}
	else
	{
		dir += 3;
		if (dir > 4)
			dir -= 4;
	}
}

void GroundVehicle::sinkTankCarcass(string *map)
{
	int i = y / 32;
	int j = x / 32;

	switch (dir)
	{
	case 1: i++; break;
	case 4: j++; break;
	}

	if (map[i][j] == 'W')
	{
		if (pusher != NULL && static_cast<Tank*>(pusher)->destValue != 0)
		{
			static_cast<Tank*>(pusher)->drownedTanks++;
			if (static_cast<Tank*>(pusher)->drownedTanks >= static_cast<Tank*>(pusher)->destValue)
			{
				static_cast<Tank*>(pusher)->isSpeedBonusUp = static_cast<Tank*>(pusher)->isShowSpeedBonusAchiev = true;

				if (static_cast<Tank*>(pusher)->army == "player")
					static_cast<Tank*>(pusher)->destValue = static_cast<Tank*>(pusher)->destValue < 80 ?
					static_cast<Tank*>(pusher)->destValue * 2 : 0;
				else
					static_cast<Tank*>(pusher)->drownedTanks = 3;
			}
			pusher = NULL;
		}

		anim.sprite.setColor(Color::Transparent);
		this->isDrowned = true;
	}
}
