#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include <vector>

using namespace sf;

class Animation
{
public:
	double frame;
	double speed;
	Sprite sprite;
	Sound sound;

	std::vector<IntRect> frames;

	//.:: Constructors :::
	Animation();
	Animation(Texture&, SoundBuffer&, int, int, int, int, double, int);

	//.:: Destructor :::
	virtual ~Animation();

	//.:: Methods_of_class :::
	void update(double, bool, int);
	bool isEnd(double);
};
