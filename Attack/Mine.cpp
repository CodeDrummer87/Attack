#include "Mine.h"

Mine::Mine()
{}

Mine::Mine(Animation &anim_, GroundVehicle *own_)
	:Entity(anim_, own_->getCoordX(false), own_->getCoordY(false), "mine", 1, true)
{
	z_index = (short)1;
	army = "enemy";
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
