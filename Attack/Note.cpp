#include "Note.h"

Note::Note()
{}

Note::Note(string message, int fontSize_, float X, float Y)
{
	font.loadFromFile("source/fonts/lik_Ascent_2_starDom.otf");
	fontSize = fontSize_;
	x = X;
	y = Y;

	text.setString(message);
	text.setFillColor(Color::Red);
	text.setPosition(x, y);
}

Note::~Note()
{}
