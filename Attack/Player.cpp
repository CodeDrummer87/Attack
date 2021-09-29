#include "Player.h"


Player::Player()
{}

Player::Player(Animation &anim, double x_, double y_, string name_, int dir_, bool isPlayAnimation_,
	Animation &aExplosion, string army_) : Tank(anim, x_, y_, name_, dir_, isPlayAnimation_, aExplosion, army_)
{
	totalKills = 0;
	currentExperience = 0;
	requiredExperience = 0;

	hasRank = preferment = isCommander = false;
}

Player::~Player()
{}
