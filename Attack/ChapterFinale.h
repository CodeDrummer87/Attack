#pragma once

#include <SFML\Graphics.hpp>

void showChapterFinale(int sizeX, int sizeY)
{
	using namespace sf;

	RenderWindow app(VideoMode(sizeX, sizeY), "Chapter Finale" , Style::Fullscreen);
	app.setMouseCursorVisible(false);

	Font font;
	font.loadFromFile("source/fonts/protosans56.ttf");

	float indent = 0;
	if (sizeX != 1280 && sizeY != 1024)
		indent = (float)sizeX / 2 - (float)(sizeX / 3.4f);

	Text text("C H A P T E R   F I N A L E", font, 75);
	text.setFillColor(Color::Yellow);
	text.setPosition(indent, (float)sizeY / 10);	//575

	Text exit("Press ESC for EXIT", font, 32);
	exit.setFillColor(Color::Red);
	exit.setPosition(sizeX / 2, sizeY / 2);

	while (app.isOpen())
	{
		if (Keyboard::isKeyPressed(Keyboard::Escape))
			app.close();

		app.clear(Color::Black);
		app.draw(text);
		app.draw(exit);
		app.display();
	}
}

bool checkTeamForSurvivors(vector<Player*> team)
{
	for (auto p : team)
	{
		if (p->status != DEAD)
			return true;
	}

	return false;
}