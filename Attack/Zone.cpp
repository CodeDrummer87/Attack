#include "Zone.h"
#include "Player.h"

Zone::Zone()
{}

Zone::Zone(Entity *own_, float radius)
{
	z_index = (short)1;

	name = "scannedZone";
	own = own_;
	army = own->army;
	number = own->number;

	zone = CircleShape(radius);
	zone.setOrigin(zone.getGlobalBounds().width / 2, zone.getGlobalBounds().height / 2);

	setPosition();

	isExist = true;
	status = ALIVE;
}

Zone::~Zone()
{}

void Zone::setPosition()
{
	x = own->getCoordX(false);
	y = own->getCoordY(false);

	zone.setPosition(x, y);
}

void Zone::update(double time)
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
