#pragma once

#include "Air.h"

struct FirstBomb
{
	bool openPosition;
	Entity *bomb;
};

class Bomb : public Air
{
private:
	Animation animSpare;
public:
	static FirstBomb firstBomb;

	//.:: Constructors :::::::::::::::::::::
	Bomb();
	Bomb(Animation&, Animation&, double, double, string);

	//.:: Destructor :::::::::::::::::::::::
	virtual ~Bomb();

	//.:: Methods_of_class :::::::::::::::::
	void update(double);
};