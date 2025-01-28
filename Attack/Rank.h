#pragma once

#include "Entity.h"
#include "Player.h"

class Rank : public Entity
{
private:
	Player * own;

public:
	//.:: Constructor :::::::::::::::::::::::
	Rank();
	Rank(Animation&, Player*, string);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Rank();

	//.:: Methods_of_class ::::::::::::::::::
	void update(double);

};
