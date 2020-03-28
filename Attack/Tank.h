#pragma once

#include "Entity.h"

using namespace sf;

class Tank : public Entity
{
private:

public:
	//.:: Constructor :::::::::::::::::::::
	Tank();
	//.:: Destructor :::::::::::::::::::::::
	virtual ~Tank();

	//.:: Methods_of_class :::::::::::::::::
	void update(double);
	void accelerate(int, double);		// direction and accelerate
};