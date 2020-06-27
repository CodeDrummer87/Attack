#pragma once

#include "Entity.h"

enum BombStatus { ABOARD, DROPPED, DESCENT };

class Air : public Entity
{
private:
	Entity *attachedObject;
public:
	static BombStatus bombStatus;
	static bool isExistFighter;
	static bool isViewToBomb;
	static Air* bomb;
	static bool setCurrentCamera;

	//.:: Constructors :::::::::::::::::::::
	Air();
	Air(Animation&, int, int, int, string, Entity*);

	//.:: Destructor :::::::::::::::::::::::
	virtual ~Air();

	//.:: Methods_of_class :::::::::::::::::
	void update(double);
};