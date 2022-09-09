#pragma once

#include "Entity.h"
#include "Boss.h"

class OilPuddle : public Entity
{
private:
	static int puddleCounter;

public:
	int adsorptionTime;
	bool isAdsorption;

	//.:: Constructor :::::::::::::::::::::::
	OilPuddle();
	OilPuddle(Animation&, double, double, int, bool, int);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~OilPuddle();

	//.:: Methods_of_class ::::::::::::::::::
	void update(double);

};
