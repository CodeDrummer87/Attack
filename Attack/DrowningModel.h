#pragma once

#include "Entity.h"
#include "Tank.h"

class DrowningModel : public Entity
{
private:
	Tank *own;

public:

	//.:: Constructor :::::::::::::::::::::::
	DrowningModel();
	DrowningModel(Animation&, Tank*, string);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~DrowningModel();

	//.:: Public_methods_of_class :::::::::::
	void update(double);
	void draw(RenderWindow&);

};

