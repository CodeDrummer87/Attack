#include "DrowningModel.h"

DrowningModel::DrowningModel()
{}

DrowningModel::DrowningModel(Animation &a, GroundVehicle *own_, string name_)
{
	anim = a;
	level = 0;
	dir = own_->dir;
	isPlayAnimation = true;
	name = name_;
	own = own_;
	x = own->getCoordX(false);
	y = own->getCoordY(false);
	anim.sprite.setPosition(x, y);
	anim.sprite.setColor(Color::Cyan);
	isExist = true;
	status = ALIVE;
}

DrowningModel::~DrowningModel()
{}

void DrowningModel::update(double time)
{
	if (isExist)
	{
		if (anim.isEnd(time))
		{
			if (own->army == "enemy")
				own->isExist = false;
			isExist = false;
		}
	}
}

void DrowningModel::draw(RenderWindow &app)
{
	anim.sprite.setPosition(x, y);
	app.draw(anim.sprite);
}
