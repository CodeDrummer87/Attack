#pragma once

#include "Entity.h"
#include "Tank.h"

class Rank : public Entity
{
private:
	Tank * own;

public:
	//.:: Constructor :::::::::::::::::::::::
	Rank();
	Rank(Animation&, Tank*, string);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Rank();

	//.:: Methods_of_class ::::::::::::::::::
	void update(double);

};
