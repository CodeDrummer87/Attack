#pragma once

#include "Tank.h"

class Enemy : public Tank
{
public:
	int currentDir;
	//.:: Constructors ::::::::::::::::::::::
	Enemy();
	Enemy(Animation&, Animation&, int, int, int, int);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Enemy();

	//.:: Methods_of_class ::::::::::::::::::
	void update(double);
	bool checkDir();
	void changeDir();
};

