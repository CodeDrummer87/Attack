#pragma once
#include "Entity.h"

struct IconAnim
{
	Animation &anim;
	char iconType;
};

class Icon : public Entity
{
public:
	char iconType;

	static int spawnTimer;
	static bool isFirstIcon;
	static int iconCounter;

	//.:: Constructor ::::::::::::::::::::::
	Icon();
	Icon(IconAnim[], double, double, int);

	//.:: Destructor :::::::::::::::::::::::
	virtual ~Icon();

	//.:: Methods_of_class :::::::::::::::::
	void update(double);

};
