#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include <vector>

using namespace sf;
using namespace std;

class Animation
{
private:
	Sound sound;
public:
	float frame, speed;
	Sprite sprite;

	vector<IntRect> frames;
	//.:: Constructors ::::::::::::::::::::::
	Animation();
	Animation(Texture &t, SoundBuffer&, int, int, int, int, double, int);	// texture, coordinates: x, y; width, height, animation_speed, frames_count
	Animation(Texture&, int, int, int, int, double, int);

	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Animation();

	//.:: Methods_of_class ::::::::::::::::::
	void update(double, bool, int);
	bool isEnd(double);
};