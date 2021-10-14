#pragma once

#include "Entity.h"
#include "Player.h"

class Air : public Entity
{
private:
	Animation animSpare;
	Player * own;

public:
	int number;

	//.:: Constructor ::::::::::::::::::::::
	Air();
	Air(Animation&, Animation&, Player*, string);

	//.:: Destructor :::::::::::::::::::::::
	virtual ~Air();

	//.:: Methods_of_class :::::::::::::::::
	void update(double);
	Player* getOwn();

};
