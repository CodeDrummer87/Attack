#pragma once

#include "Entity.h"
#include "Tank.h"

class AchievementModel : public Entity
{
private:
	Tank *own;

public:

	//.:: Constructor :::::::::::::::::::::::
	AchievementModel();
	AchievementModel(Animation&, Tank*, string);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~AchievementModel();

	//.:: Public_methods_of_class :::::::::::
	void update(double);
	void draw(RenderWindow&);

};
