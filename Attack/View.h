#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

View view;

void setViewCoordinates(double y)
{
	if (y > 1610)
		y = 1610;

	if (y < 540)
		y = 540;

	view.setCenter(960, y);
}