#include "Area.h"
#include "Player.h"

Area::Area()
{}

Area::Area(Entity *own_, float radius)
{
	z_index = (short)1;

	name = "area";
	own = own_;
	army = own->army;

	area = CircleShape(radius);
	area.setOrigin(area.getGlobalBounds().width / 2, area.getGlobalBounds().height / 2);

	setPosition();

	isExist = true;
	status = ALIVE;
}

Area::~Area()
{}

void Area::setPosition()
{
	x = own->getCoordX(false);
	y = own->getCoordY(false);

	area.setPosition(x, y);
}

void Area::update(double time)
{
	if (isExist)
	{
		setPosition();

		if (static_cast<Player*>(own)->isDisplayPartisanAchievement)
			isExist = false;

		if (own->name == "destroyed" && static_cast<Player*>(own)->lives == 0)
			isExist = false;
	}
}
