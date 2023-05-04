#pragma once
#include "Entity.h"

class Icon : public Entity
{
private:
	Animation appearAnim;
	Entity *player;

public:

	static int spawnTimer;

	//.:: Constructor ::::::::::::::::::::::
	Icon();
	Icon(Animation[], Animation&, Entity*, int);

	//.:: Destructor :::::::::::::::::::::::
	virtual ~Icon();

	//.:: Methods_of_class :::::::::::::::::
	void update(double);

};
