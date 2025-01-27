#pragma once

#include "libraries.h"

class Note
{
private:
	Font font;
	int fontSize;
	float x;
	float y;

public:
	Text text;	

	//.:: Constructor :::::::::::::::::::::::
	Note();
	Note(string, int, float, float);
	Note(string,float, float);

	//.:: Destructor ::::::::::::::::::::::::
	~Note();

	//.:: Methods_of_class  :::::::::::::::::
	void draw(RenderWindow&);

};

