#pragma once

#include "Entity.h"

class CurrentMessage : public Entity
{
private:
	Text message;

public:
	bool isCreated;
	int endDisplayTime;

	//.:: Constructor :::::::::::::::::::::::
	CurrentMessage();
	CurrentMessage(string, Font, unsigned int, Color, string);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~CurrentMessage();

	//.:: Methods_of_class ::::::::::::::::::
	void update();
	void draw(RenderWindow&);

};