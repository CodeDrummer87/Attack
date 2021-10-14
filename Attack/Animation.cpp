#pragma once

#include "Animation.h"

Animation::Animation() {}

Animation::Animation(Texture& t, int x, int y, int width, int height, double animSpeed, int count)
{
	frame = 0;
	speed = animSpeed;

	for (int i = 0; i < count; i++)
		frames.push_back(IntRect(x + i * width, y, width, height));

	sprite.setTexture(t);
	sprite.setOrigin(width / 2, height / 2);
	sprite.setTextureRect(frames[0]);
}

Animation::Animation(Texture& t, SoundBuffer& b, int x, int y, int width, int height, double animSpeed, int count)
{
	frame = 0;
	speed = animSpeed;

	for (int i = 0; i < count; i++)
	{
		frames.push_back(IntRect((x + i * width), y, width, height));
	}
	sprite.setTexture(t);
	sprite.setOrigin(width / 2, height / 2);
	sprite.setTextureRect(IntRect(frames[0]));

	sound.setBuffer(b);
	sound.setLoop(true);
	sound.setPitch(0.9f);
	sound.setVolume(40.f);
}

Animation::~Animation() {}

void Animation::update(double time, bool on, int dir)
{
	int frameCount;

	switch (dir)
	{
	case 1:
		sprite.setRotation(0);
		break;

	case 2:
		sprite.setRotation(90);
		break;

	case 3:
		sprite.setRotation(180);
		break;

	case 4:
		sprite.setRotation(270);
		break;

	default:
		sprite.setRotation(dir);
	}

	frameCount = frames.size();

	sound.pause();

	if (on)
	{
		sound.play();
		frame += speed * time;
		if (frame >= frameCount)
			frame -= frameCount;
	}
	if (frameCount > 0)
		sprite.setTextureRect(frames[(int)frame]);
}

bool Animation::isEnd(double time)
{
	return frame + speed * time >= frames.size();
}

FloatRect Animation::getRect(int dir)
{
	FloatRect rect = sprite.getGlobalBounds();
	switch (dir)
	{
	case 1: return FloatRect(rect.left, rect.top, 39, 52);
	case 2: return FloatRect(rect.left, rect.top, 52, 39);
	case 3: return FloatRect(rect.left, rect.top, 52, 52);
	case 4: return FloatRect(rect.left, rect.top, 39, 52);
	default: return rect;
	}
}

FloatRect Animation::getShellRect(bool isShell)
{
	FloatRect rect = sprite.getGlobalBounds();

	if (isShell)
		return FloatRect(rect.left, rect.top, 8, 8);
	else
		return FloatRect(rect.left, rect.top, 27, 27);
}
