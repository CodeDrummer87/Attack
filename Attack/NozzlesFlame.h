#pragma once

#include "Entity.h"
#include "Boss.h"

class NozzlesFlame : public Entity
{
private:
	Animation firstLeft;
	Animation secondLeft;
	Animation thirdLeft;

	Animation firstRight;
	Animation secondRight;
	Animation thirdRight;

	Boss* boss;

	bool wasSecondStepWent;
	bool wasThirdStepWent;

	//.:: Methods_of_class ::::::::::::::::::
	void setSpritesPosition();
	float calculateAngle(string);

public:

	//.:: Constructor :::::::::::::::::::::::
	NozzlesFlame();
	NozzlesFlame(Animation&, Boss*);

	//.:: Destructor ::::::::::::::::::::::::
	~NozzlesFlame();

	//.:: Methods_of_class ::::::::::::::::::
	void update(double);
	void draw(RenderWindow&);

};
