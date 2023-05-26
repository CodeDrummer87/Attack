#pragma once
#include "Entity.h"

struct IconAnim
{
	Animation &anim;
	char iconType;
};

class Icon : public Entity
{
private:
	Animation appearAnim;
	Entity *player;

public:

	static int spawnTimer;
	static bool isFirstIcon;
	char iconType;

	//.:: Constructor ::::::::::::::::::::::
	Icon();
	Icon(IconAnim[], Animation&, Entity*, int);

	//.:: Destructor :::::::::::::::::::::::
	virtual ~Icon();

	//.:: Methods_of_class :::::::::::::::::
	void update(double);

};
