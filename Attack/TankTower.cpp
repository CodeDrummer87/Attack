#pragma once
#pragma warning(disable:6011)

#include "TankTower.h"
#include "Boss.h"

TankTower::TankTower()
{}

TankTower::TankTower(TankTowerArgs& args)
	: Enemy(args.anim, args.own->getCoordX(false), args.own->getCoordY(false), args.sExplosion, args.own->level)
{
	z_index = (short)4;

	name = "turret";
	army = "enemy";
	own = args.own;
	currentTarget = NULL;
	isTargetSearch = true;
	explosionFrameCount = 11;

	isFirstShot = isSecondShot = true;
	isPlayAnimation = roundFirst = roundSecond = isMortarShotTime = isRampageAccumulating = false;
	actionTime = 0;

	dir = 180;

	scannedZone = CircleShape(550.f);
	scannedZone.setOrigin(scannedZone.getGlobalBounds().width / 2, scannedZone.getGlobalBounds().height / 2);
	scannedZone.setPosition(x, y);
}

TankTower::~TankTower()
{}

void TankTower::update(double time)
{
	if (isDestroyed)
	{
		if (isPlayAnimation)
			isPlayAnimation = false;
	}
	else
	{
		if (status != DEAD && !own->isAiming)
		{
			x = own->getCoordX(false);
			y = own->getCoordY(false);

			scannedZone.setPosition(x, y);

			if (!isTargetSearch && (currentTarget != NULL || currentTarget->status != DEAD))
			{
				int angle = takeAim(currentTarget);
				if (dir != angle)
					getRotationDirection(dir, angle);			
			}
			else
				dir = own->dir;

			if (currentTarget != NULL && currentTarget->status == DEAD)
			{
				currentTarget = NULL;
				isTargetSearch = true;
				own->isAiming = false;
				own->aimingTime = 0;
			}
		}

		if (!own->isExist)
			isExist = false;

		if (own->status == WOUNDED && status != WOUNDED)
		{
			status = WOUNDED;
			anim.setFrames(0, 128, 128, 128, 1, 1);
			anim.sound.setPitch(0.5f);
		}

		if (own->status == DEAD && status != DEAD)
			status = DEAD;

		if (status == DEAD)
		{
			if (isTransition)
			{
				if (anim.isEnd(time))
				{
					anim.frames[0] = IntRect(0, 384, 128, 128);
					anim.sound.stop();
					isDestroyed = true;
				}
				else
				{
					dir++;
					x += 0.4;
					y -= 0.4;
				}
			}
			else
			{
				name = "destroyed";
				isPlayAnimation = true;
				anim.setFrames(0, 256, 128, 128, 11, 0.008);
				isTransition = true;
			}
		}
	}
}

void TankTower::detectTarget(Player* player, int mapIndex, int currentTime)
{
	FloatRect bossZone = scannedZone.getGlobalBounds();
	FloatRect target = player->anim.sprite.getGlobalBounds();

	if (bossZone.intersects(target))
	{
		currentTarget = player;
		isTargetSearch = false;

		switch (mapIndex)
		{
		case 1: 
			own->aimingTime = currentTime + 10;
			actionTime = currentTime + 14;
			break;

		case 2: break;
		case 3: break;
		case 4: break;
		case 5: break;

		default:
			own->aimingTime = currentTime + 12;
			actionTime = currentTime + 16;
		}
	}	
}

int TankTower::takeAim(GroundVehicle *player)
{
	double value = (y - player->getCoordY(false)) / (x - player->getCoordX(false));
	int angle = atan(value) * 180 / 3.14;

	if (x < player->getCoordX(false)) angle += 90;
	if (x > player->getCoordX(false)) angle += 270;

	if (x == player->getCoordX(false) && y > player->getCoordY(false)) angle = 0;
	if (x == player->getCoordX(false) && y < player->getCoordY(false)) angle = 180;
	if (y == player->getCoordY(false) && x > player->getCoordX(false)) angle = 270;

	return angle;
}
 
void TankTower::getRotationDirection(int &d, int &a) //.:: d - dir, a - angle
{
	int value = d > a ? d - a : a - d;

	(d > a && value < 180) ? d-- : (d > a && value > 180) ? d++ : d < a && value < 180 ? d++ : d--;
	resetDegrees(d);
}

void TankTower::destroyPlayerByCannon()
{
	if (isShot && (dir == 0 || dir == 90 || dir == 180 || dir == 270))
		round = true;
}

void TankTower::destroyPlayerByCannons()
{
	if (dir == 0 || dir == 90 || dir == 180 || dir == 270)
	{
		roundFirst = isFirstShot;
		roundSecond = isSecondShot;
	}
}

void TankTower::setNextAimingTime(int currentTime)
{
	own->isAiming = false;
	own->aimingTime = currentTime + 12;
	
	isMortarShotTime = false;
	actionTime = currentTime + 16;
}

Tank* TankTower::getTargetForMortar(vector<Player*> players)
{
	int index;
	int counter = 0;
	while (true)
	{
		++counter;
		if (counter == 50) return NULL;

		index = rand() % players.size();
		if (players[index]->status != Status::DEAD)
			return players[index];
	}
}

void TankTower::checkMortarShotTime(int currentTime)
{
	if (!isTargetSearch && actionTime == currentTime && (currentTarget != NULL || currentTarget->status != DEAD))
		isMortarShotTime = true;
}

void TankTower::checkRampageAccumulation(int currentTime)
{
	if (!isTargetSearch && actionTime == currentTime && (currentTarget != NULL || currentTarget->status != DEAD))
		isRampageAccumulating = true;
}

void TankTower::chooseBehavior(int mapIndex, int gameTime)
{
	switch (mapIndex)
	{
	case 1:
		destroyPlayerByCannon();
		checkRampageAccumulation(gameTime);

		if (isRampageAccumulating)
		{
			isRampageAccumulating = false;
			
			own->isAiming = false;
			own->aimingTime = gameTime + 20;
			actionTime = gameTime + 24;

			own->speedBonus = 10.f;
		}

		own->slowDownSpeed();

		break;

	default:
		destroyPlayerByCannons();
		checkMortarShotTime(gameTime);
	}
}
