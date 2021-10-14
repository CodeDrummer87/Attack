#pragma once

#include "libraries.h"

class Animation
{
public:
	double frame;
	double speed;
	Sprite sprite;
	Sound sound;

	vector<IntRect> frames;

	//.:: Constructors :::
	Animation();
	Animation(Texture&, int, int, int, int, double, int);
	Animation(Texture&, SoundBuffer&, int, int, int, int, double, int);

	//.:: Destructor :::
	virtual ~Animation();

	//.:: Methods_of_class :::
	void update(double, bool, int);
	bool isEnd(double);
	FloatRect getRect(int);
	FloatRect getShellRect(bool);

};
