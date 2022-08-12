#pragma once

#include "GroundVehicle.h"
#include "Tank.h"

extern View view;

GroundVehicle::GroundVehicle()
{}

GroundVehicle::GroundVehicle(Animation &anim, double x_, double y_, string name_, int dir_, bool isPlayAnimation_,
	SoundBuffer &sExplosion_, int expFrameCount, string army_, int level_)
	: Entity(anim, x_, y_, name_, dir_, isPlayAnimation_)
{
	army = army_;
	level = level_;
	status = ALIVE;
	sExplosion = sExplosion_;
	explosionFrameCount = expFrameCount;

	speedBonus = 0.0f;
	isDestroyed = isTransition = drowning = isSmoking = false;
	isDrowned = isShowRepair = isPlayerControl = isSkidding = false;
	hitPoints = level + 1;
	toUp = toDown = toRight = toLeft = 0;

	pusher = NULL;

	traffic.up.dir = true;		traffic.up.barId = 0;
	traffic.right.dir = true;	traffic.right.barId = 0;
	traffic.down.dir = true;	traffic.down.barId = 0;
	traffic.left.dir = true;	traffic.left.barId = 0;
	traffic.areDirectionsOpen = true;

	number = ++counter;
	puddleId = 0;

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
				x += isSkidding? dx / 2.5 : dx;
			if (y + dy > 0 && y + dy < 119 * 32)
				y += isSkidding? dy / 2.5 : dy;
			
			dx = dy = 0;
		}
		else if (status == WOUNDED)
		{
			x += isSkidding? dx / 4 : dx / 1.5;
			y += isSkidding? dy / 4 : dy / 1.5;
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
				anim.setFrames(0, 64, 64, 64, explosionFrameCount, 0.01);
				anim.sound.setBuffer(sExplosion);
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

void GroundVehicle::checkMapCollision(string *map)
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
			if (map[i][j] == 'R' && (hitPoints < 1 + level))
			{
				sound.play();
				++hitPoints;
				isShowRepair = true;
				map[i][j] = ' ';
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

void GroundVehicle::checkPuddlesCollision(Entity *p)
{
	if (puddleId == 0 || puddleId == p->number)
	{
		FloatRect tank = (dir == 1 || dir == 3) ? FloatRect(x, y, 40, 52) : FloatRect(x, y, 52, 40);
		FloatRect puddle = FloatRect(p->getCoordX(false) + 10, p->getCoordY(false) + 12, 30, 30);

		if (tank.intersects(puddle))
		{
			if (!isSkidding && puddleId == 0 && p->level == 1)
				resetSkidding(false, p->number);

			if (!isSkidding && puddleId == p->number && p->level == 2)
				resetSkidding(true, p->number);
		}
		else
			if (isSkidding)
				resetSkidding(true, p->number);

		if (p->level == 2 && isSkidding)
			resetSkidding(true, p->number);
	}
}

void GroundVehicle::resetSkidding(bool isApply, int puddleId_)
{
	if (isApply)
	{
		isSkidding = false;
		puddleId = 0;
		anim.sound.setPitch(status == ALIVE && army == "player" ? 0.9f : 0.5f);
	}
	else
	{
		isSkidding = true;
		puddleId = puddleId_;
		anim.sound.setPitch(army == "player" ? 2.5f : 0.9f);
	}
}

void GroundVehicle::checkBossCollision(GroundVehicle *boss_, Sound &sBossLaugh)
{
	double bX = (boss_->dir == 1 || boss_->dir == 3) ? boss_->getCoordX(false) - 43 : boss_->getCoordX(false) - 52;
	double bY = (boss_->dir == 1 || boss_->dir == 3) ? boss_->getCoordY(false) - 52 : boss_->getCoordY(false) - 43;
	FloatRect boss = (boss_->dir == 1 || boss_->dir == 3) ? FloatRect(bX, bY, 86, 104) : FloatRect(bX, bY, 104, 86);

	double bpX = (boss_->dir == 1 || boss_->dir == 3) ? boss_->getCoordX(false) - 38 : boss_->getCoordX(false) - 47;
	double bpY = (boss_->dir == 1 || boss_->dir == 3) ? boss_->getCoordY(false) - 47 : boss_->getCoordY(false) - 38;
	FloatRect bossPressingPart = (boss_->dir == 1 || boss_->dir == 3) ? FloatRect(bpX, bpY, 76, 94) : FloatRect(bpX, bpY, 94, 76);

	double tX = (dir == 1 || dir == 3) ? x - 25 : x - 19;
	double tY = (dir == 1 || dir == 3) ? y - 19 : y - 25;
	FloatRect tank = (dir == 1 || dir == 3) ? FloatRect(tX, tY, 37, 49) : FloatRect(tX, tY, 49, 37);

	if (tank.intersects(boss))
	{
		if (tank.intersects(bossPressingPart))
		{
			if (hitPoints > 0)
			{
				hitPoints = 0;
				sBossLaugh.play();
			}
		}
		else
		{
			dx = dir == 2 || dir == 4 ? 0 : dx;
			dy = dir == 1 || dir == 3 ? 0 : dy;
		}
	}
}
