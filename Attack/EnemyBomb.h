#pragma once

#include "Air.h"

class EnemyBomb : public Air
{
private:
	Animation bombExplosion;

public:
	bool coordsTransmitted;

	//.:: Constructor ::::::::::::::::::::::
	EnemyBomb();
	EnemyBomb(Animation&, Animation&, double, double, string);

	//.:: Destructor :::::::::::::::::::::::
	virtual ~EnemyBomb();

	//.:: Methods_of_class :::::::::::::::::
	void update(double);

};

