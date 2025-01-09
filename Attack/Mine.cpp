#include "Mine.h"

Mine::Mine()
{}

Mine::Mine(Animation &anim_, GroundVehicle *own_, int mineLevel)
	:Entity(anim_, own_->getCoordX(false), own_->getCoordY(false), "mine", 1, true)
{
	z_index = (short)1;
	army = "enemy";
	level += mineLevel;
	damage = level + (rand() % 7 + 1);
}

Mine::~Mine()
{}

void Mine::update(double time)
{
	if (isExist)
	{
		if (status == Status::DEAD)
			isExist = false;
	}
}

bool Mine::checkMineCollision(GroundVehicle* vehicle)
{
	FloatRect mine = this->anim.sprite.getGlobalBounds();
	FloatRect player = vehicle->anim.getRect(vehicle->dir);

	if (mine.intersects(player))
	{
		this->status = Status::DEAD;
		return true;
	}

	return false;
}

bool Mine::isActivatedMine(GroundVehicle* vehicle)
{
	return Mine::checkMineCollision(vehicle);
}

bool Mine::exploseMine(GroundVehicle* player)
{
	int explosionProbability = rand() % 10 + 1;

	if (explosionProbability > 5)
		return false;

	player->hitPoints -= damage;
	return true;
}
