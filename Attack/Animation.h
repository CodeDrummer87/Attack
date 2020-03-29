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

	//.:: For essential animation (not movement)
	vector<IntRect> frames;

	//.:: Tank movement
	vector<IntRect> toUp;
	vector<IntRect> toRight;
	vector<IntRect> toDown;
	vector<IntRect> toLeft;
	//.:: Constructors ::::::::::::::::::::::
	Animation();
	Animation(Texture &t, SoundBuffer&, int, int, int, int, double, int);	// texture, coordinates: x, y; width, height, animation_speed, frames_count
	
	//.:: Destructor ::::::::::::::::::::::::
	virtual ~Animation();

	//.:: Methods_of_class ::::::::::::::::::
	void update(double, bool, int);
};

