#pragma once

#include "Air.h"

struct FirstBomb
{
	bool isOpenPosition;
	Entity *bomb;
};

class Bomb : public Air
{
private:
	Animation animSpare;

public:
	static FirstBomb firstBomb;
	bool coordsTransmitted;

	//.:: Constructor ::::::::::::::::::::::
	Bomb();
	Bomb(Animation&, Animation&, double, double, string);

	//.:: Destructor :::::::::::::::::::::::
	virtual ~Bomb();

	//.:: Methods_of_class :::::::::::::::::
	void update(double);

};
